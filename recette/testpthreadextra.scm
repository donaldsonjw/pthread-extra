;;;; Copyright(c) 2010 Joseph Donaldson(donaldsonjw@yahoo.com) 
;;;; This file is part of Pthread-extra.
;;;;
;;;;     Pthread-extra is free software: you can redistribute it and/or modify
;;;;     it under the terms of the GNU Lesser General Public License as
;;;;     published by the Free Software Foundation, either version 3 of the
;;;;     License, or (at your option) any later version.
;;;;
;;;;     Pthread-extra is distributed in the hope that it will be useful, but
;;;;     WITHOUT ANY WARRANTY; without even the implied warranty of
;;;;     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
;;;;     Lesser General Public License for more details.
;;;;
;;;;     You should have received a copy of the GNU Lesser General Public
;;;;     License along with Pthread-extra.  If not, see
;;;;     <http://www.gnu.org/licenses/>.
(module testpthreadextra
   (library pthread)
   (library pthread-extra)
   (main main))


;;;; testing infrastructure copied from the recette for Bigloo's pthread library

;*---------------------------------------------------------------------*/
;*    *tests* ...                                                      */
;*---------------------------------------------------------------------*/
(define *tests* '())

;*---------------------------------------------------------------------*/
;*    *failure* and *success* ...                                      */
;*---------------------------------------------------------------------*/
(define *failure* '())
(define *success* 0)

;*---------------------------------------------------------------------*/
;*    test ...                                                         */
;*---------------------------------------------------------------------*/
(define (test name prgm::procedure res)
   (display* name "...")
   (flush-output-port (current-output-port))
   (let ((provided (with-handler
		      (lambda (e)
			 (error-notify e)
			 (vector res))
		      (prgm))))
      (if (or (eq? res #unspecified)
	      (and (procedure? res) (res provided))
	      (equal? res provided))
	  (begin
	     (set! *success* (+fx 1 *success*))
	     (print "ok."))
	  (begin
	     (set! *failure* (cons name *failure*))
	     (print "error.")
	     (print "   ==> provided: [" provided
		    "]\n       expected: ["
		    (if (procedure? res) (res 'result) res)
		    "]")))))

;*---------------------------------------------------------------------*/
;*    define-test ...                                                  */
;*---------------------------------------------------------------------*/
(define-macro (define-test id prgm . rest)
   (let ((t (match-case rest
	       ((:result ?result)
		`(list ',id (lambda () ,prgm) ,result))
	       (()
		`(list ',id (lambda () ,prgm) #unspecified))
	       (else
		(error "define-test" "Illegal rest argument" rest)))))
      `(set! *tests* (cons ,t *tests*))))




;*---------------------------------------------------------------------*/
;*    main ...                                                         */
;*---------------------------------------------------------------------*/
(define (main argv)
   (let ((tests '()))
      (args-parse (cdr argv)
	 ((("-h" "--help") (help "This help message"))
	  (args-parse-usage #f)
	  (exit 0))
	 (else
	  (set! tests (cons (string->symbol else) tests))))
      ;; run all the tests
      (for-each (lambda (pvn)
		   (apply test pvn))
		(if (null? tests)
		    (reverse *tests*)
		    (reverse (filter (lambda (t) (memq (car t) tests))
				     *tests*))))
      ;; if we reach that point, we are done
      (print "\n"
	     (if (null? tests) "All" (reverse tests))
	     " tests executed...\n"
	     (if (null? *failure*)
		 "all succeeded"
		 (format " ~a succeeded\n ~a failed ~a"
			 *success*
			 (length *failure*)
			 (reverse *failure*))))))



;;;; cond-expand	   
(define-test cond-expand 
   (cond-expand	   
      (pthread-extra #t) 
      (else #f))	   
   :result #t)	   



;;;; make-work-queue
(define-test make-work-queue
   (make-work-queue 3)
   :result (lambda (v)
	      (if (eq? v 'result)
		  "a work-queue"
		  (work-queue? v))))


(define-test work-queue-empty?
   (make-work-queue 3)
   :result (lambda (v)
	      (if (eq? v 'result)
		  "a empty work-queue"
		  (work-queue-empty? v))))

(define-test work-queue-push!
   (with-output-to-string
      (lambda ()
	 (let ((m (make-mutex))
	       (q (make-work-queue 2)))
	    (work-queue-push! q (lambda () (with-lock m (lambda () (write 1) (flush-output-port (current-output-port))))))
	    (work-queue-push! q (lambda () (with-lock m (lambda () (write 2) (flush-output-port (current-output-port))))))
	    (work-queue-finish! q))))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "12 or 21"
		  (or (equal? v "12")
		      (equal? v "21")))))


;;;; futures
(define-test make-future
   (make-future (lambda () #unspecified))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "a future"
		  (future? v))))

(define-test future-touch
   (let ((future (make-future (lambda () 5))))
      (future-touch future))
   :result (lambda (v)
	       (if (eq? v 'result)
		   "5"
		   (equal? v 5))))

(define-test future-timeout-error
   (let ((future (make-future (lambda () (thread-sleep! 5000000) 5))))
      (with-handler (lambda (e)
		       (if (isa?  e &future-timeout-error)
			   'time-out
			   (raise e)))
		    (future-touch future 1000)))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "time-out"
		  (eq? v 'time-out))))
	      

;;;; concurrent-queue
(define-test make-concurrent-queue
   (make-concurrent-queue)
   :result (lambda (v)
	      (if (eq? v 'result)
		  "the concurrent queue"
		  (concurrent-queue? v))))

(define-test concurrent-queue-empty?
   (concurrent-queue-empty? (make-concurrent-queue))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "#t"
		   v)))

(define-test enqueue&dequeue
   (let ((q (make-concurrent-queue)))
      (concurrent-queue-enqueue! q 5)
      (concurrent-queue-enqueue! q 4)
      (let* ((a (concurrent-queue-dequeue! q))
	     (b (concurrent-queue-dequeue! q)))
	 (cons a b)))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "(5 . 4)"
		  (and (equal? (car v) 5)
		       (equal? (cdr v) 4)))))

(define (enqueue-val-n-times q val count)
   (do ((i 0 (+ i 1)))
       ((= i count))
       (concurrent-queue-enqueue! q val)))

(define (dequeue-n-times q m count)
   (do ((i 0 (+ i 1)))
       ((= i count))
       (let ((item (concurrent-queue-dequeue! q)))
	  (with-lock m
	     (lambda ()
		(display item)
		(flush-output-port (current-output-port)))))))

(define (count-char str char)
   (do ((i 0 (+ i 1))
	(count 0 (if (char=? (string-ref str i) char)
		     (+ count 1)
		     count)))
       ((= i (string-length str)) count)))

(define-test multiple-threads-enqueue&dequeue
   (let* ((m (make-mutex))
	 (q (make-concurrent-queue))
	 (v (make-vector 4)))
      (vector-set! v 0 (instantiate::pthread (body (lambda () (enqueue-val-n-times q #\a 100)))))
      (vector-set! v 1 (instantiate::pthread (body (lambda () (enqueue-val-n-times q #\b 100)))))
      (vector-set! v 2 (instantiate::pthread (body (lambda () (dequeue-n-times q m  100)))))
      (vector-set! v 3 (instantiate::pthread (body (lambda () (dequeue-n-times q m 100)))))
      (with-output-to-string
	 (lambda ()
	    (do ((i 0 (+ i 1)))
		((= i (vector-length v)))
		(thread-start-joinable! (vector-ref v i)))
	    (do ((i 0 (+ i 1)))
		((= i  (vector-length v)))
		(thread-join! (vector-ref v i))))))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "a 200 character string with 100 a's and 100 b's"
		  (and (= (string-length v) 200)
		       (= (count-char v #\a) 100)
		       (= (count-char v #\b) 100)))))
      

(define-test concurrent-queue-timeout
   (let ((q (make-concurrent-queue)))
      (with-handler (lambda (e)
		       (if (isa? e &concurrent-queue-timeout-error)
			   'time-out
			   (raise e)))
		    (concurrent-queue-dequeue! q 1000)))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "time-out"
		  (eq? v 'time-out))))


;;;; actor
(define-test make-actor
   (make-actor (lambda () #unspecified))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "the actor"
		  (actor? v))))

(define-test actor-start!
   (let ((m (make-mutex))
	 (cv (make-condition-variable)))
      (with-output-to-string
	 (lambda ()
	    (let ((t (make-actor (lambda ()
				    (with-lock m
				       (lambda ()
					  (write 5)
					  (flush-output-port
					     (current-output-port))
					  (condition-variable-signal! cv)))))))
	       (with-lock m
		  (lambda ()
		     (actor-start! t)
		     (condition-variable-wait! cv m)))))))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "5"
		  (string=? v "5"))))


(define-test actor-start-joinable!
   (with-output-to-string
      (lambda ()
	 (let ((t (make-actor (lambda ()
				 (write 5)
				 (flush-output-port
				    (current-output-port))))))
	    (actor-start-joinable! t)
	    (actor-join! t))))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "5"
		  (string=? v "5"))))

(define-test actor-send
   (with-output-to-string
      (lambda ()
	 (let ((t (make-actor (lambda ()
				 (write (actor-receive (current-actor)))
				 (flush-output-port (current-output-port))))))
	    (actor-start-joinable! t)
	    (actor-send t 5)
	    (actor-join! t))))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "5"
		  (string=? v "5"))))
   

(define-test actor-receive-timeout-error
   (let ((t (make-actor
	       (lambda ()
		  (with-handler (lambda (e)
				   (if (isa?  e &actor-receive-timeout-error)
			   'time-out
			   (raise e)))
		    (actor-receive (current-actor) 1000))))))
      (actor-start-joinable! t)
      (actor-join! t))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "time-out"
		  (eq? v 'time-out))))


;;;; barriers
(define-test make-barrier
   (make-barrier 2)
   :result (lambda (v)
	      (if (eq? v 'result)
		  "the barrier"
		  (barrier? v))))




(define-test barrier-wait!
   (with-output-to-string
      (lambda ()
	 (define (create-wait-thunk b)
	    (lambda ()
	       (barrier-wait! b)))
	 (let* ((b (make-barrier 2 (lambda ()
				     (write 5)
				     (flush-output-port (current-output-port)))))
		(t1 (instantiate::pthread (body (create-wait-thunk b))))
		(t2 (instantiate::pthread (body (create-wait-thunk b)))))
	    (thread-start-joinable! t1)
	    (thread-start-joinable! t2)
	    (thread-join! t1)
	    (thread-join! t2))))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "5"
		  (equal? v "5"))))


(define-test barrier-timeout-error
   (let* ((b (make-barrier 2))
	  (t (instantiate::pthread
		(body (lambda ()
			 (with-handler (lambda (e)
					  (if (isa? e &barrier-timeout-error)
					      'time-out
					      (raise e)))
				       (barrier-wait! b 1000)))))))
      (thread-start-joinable! t)
      (thread-join! t))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "time out"
		  (eq? v 'time-out))))
	    
;;;; rw-lock
(define-test make-rw-lock
   (make-rw-lock)
   :result (lambda (v)
	      (if (eq? v 'result)
		  "the rw-lock"
		  (rw-lock? v))))


;;;; TODO need to write more rw-lock tests
  
;;;; semaphore

(define-test make-semaphore
   (make-semaphore 2)
   :result (lambda (v)
	      (if (eq? v 'result)
		  "the semaphore"
		  (semaphore? v))))

(define-test semaphore-timeout
   (let ((s (make-semaphore 1)))
      (semaphore-wait! s)
      (if (not (semaphore-wait! s 1000))
	  'time-out))
   :result (lambda (v)
	      (if (eq? v 'result)
		  "time out"
		  (eq? v 'time-out))))

; (define (ping-pong-message? msg)
;    (and (list? msg)
; 	(eq? (car msg) 'ping-pong)))

; (define (ping-pong-body msg)
;    (caddr msg))

; (define (ping-pong-sender msg)
;    (cadr msg))

; (define (make-ping-pong-message action)
;    (list 'ping-pong (current-actor) action))

; (define (make-pong-action ping count)
;    (lambda ()
;       (actor-send ping
; 		    (make-ping-pong-message 'pong))
;    (let loop ((msg (actor-receive (current-actor)))
; 	      (remaining count))
;       (if (ping-pong-message? msg)
; 	  (let ((body (ping-pong-body msg)))
; 	     (case body
; 		((ping)
; 		 (print "Pong:  ping with " remaining " remaining")
; 		 (if (> remaining 0)
; 		     (begin
; 			(actor-send ping
; 			   (make-ping-pong-message 'pong))
; 			(loop (actor-receive (current-actor))
; 			   (- remaining 1)))
; 		     (actor-send ping
; 			(make-ping-pong-message 'exit))))
; 		(else
; 		 #unspecified)))))))

; (define (ping-action)
;    (let loop ((msg (actor-receive (current-actor))))
;       (if (ping-pong-message? msg)
; 	  (let ((body (ping-pong-body msg)))
; 	     (case body
; 		((pong)
; 		 (print "Ping:  pong")
; 		 (actor-send (ping-pong-sender msg)
; 		    (make-ping-pong-message 'ping)) 
; 		 (loop (actor-receive (current-actor))))
; 		(else
; 		 #unspecified))))))

; (define (main args)
;    (let ((wq (make-work-queue 6)))
;       (work-queue-finish! wq))

;    (let* ((ping-actor (make-actor ping-action))
; 	  (pong-actor (make-actor (make-pong-action ping-actor 10))))
;       (actor-start-joinable! ping-actor)
;       (actor-start-joinable! pong-actor)
;       (actor-join! ping-actor)
;       (actor-join! pong-actor)
;      ))