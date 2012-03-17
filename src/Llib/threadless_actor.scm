;;;; Copyright(c) 2011 Joseph Donaldson(donaldsonjw@yahoo.com) 
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

;;;; An implementation of threadless actors inspired by Scala's actor library
(module threadless-actor
   (library pthread)
   (import concurrent-queue)
   (import work-queue)
   (static
    (class %threadless-actor
       name
       (body (default #unspecified))
       (continuation (default #unspecified))
       (scheduled? (default #f))
       (mutex (default (make-mutex)))
       (mailbox (default (make-concurrent-queue)))))
   (export (threadless-actor-scheduler)
	   (scheduler-push! sched thunk)
	   (scheduler-finish! sched)
	   (current-threadless-actor)
	   (threadless-actor-name actor)
	   (threadless-actor-send actor msg)
	   (threadless-actor-receive-w/cont actor cont)
	   (threadless-actor-start! actor)))


;;;; recursive mutex locking, copied from the Bigloo thread documentation

(define (mutex-lock-recursively! mutex)
   (if (eq? (mutex-state mutex) (current-thread))
          (let ((n (mutex-specific mutex)))
             (mutex-specific-set! mutex (+ n 1)))
          (begin
             (mutex-lock! mutex)
             (mutex-specific-set! mutex 0))))

(define (mutex-unlock-recursively! mutex)
      (let ((n (mutex-specific mutex)))
         (if (= n 0)
             (mutex-unlock! mutex)
             (mutex-specific-set! mutex (- n 1)))))

(define (with-recursive-lock lock thunk)
   (mutex-lock-recursively! lock)
   (unwind-protect
      (thunk)
      (mutex-unlock-recursively! lock)))

;;;; threadless actor implementation inspired by Scala

(define +threadless-actor-scheduler+ #unspecified)

(define (threadless-actor-scheduler)
 (when (eq? +threadless-actor-scheduler+ #unspecified)
    (set! +threadless-actor-scheduler+ (make-work-queue 6)))
    +threadless-actor-scheduler+)

(define (scheduler-push! sched thunk)
   (work-queue-push! sched thunk))

(define (scheduler-finish! sched)
   (work-queue-finish! sched))

(define (current-threadless-actor)
   (let ((res (thread-parameter 'current-threadless-actor)))
      (if res
	  res
	  #unspecified)))

(define (threadless-actor-name actor)
   (let ((actor::%threadless-actor actor))
      (-> actor name)))

(define (current-threadless-actor-set! a)
   (thread-parameter-set! 'current-threadless-actor a))


(define (make-threadless-actor body #!optional (name (gensym 'threadless-actor)))
   (let* ((a::%threadless-actor
	     (instantiate::%threadless-actor (name name) (body #unspecified)))
	  (b (lambda () (current-threadless-actor-set! a) (body))))
      (set! (-> a body) b)
      a))

(define (threadless-actor? actor)
   (isa? actor %threadless-actor))

(define (threadless-actor-send actor msg)
   (with-access::%threadless-actor actor (mailbox mutex scheduled? continuation)
      ;(print "scheduled?= " scheduled?)
      ;(print "continuation= " continuation)
      (with-recursive-lock mutex
	 (lambda ()
	    (if (and (not (eq? continuation #unspecified))
		     (not scheduled?))
		(let ((curr-actor (current-threadless-actor)))
		   (with-handler
		      (lambda (e)
			 (set! scheduled? #f)
			 (if (eq? e 'suspended-actor)
			     #unspecified
			     (raise e)))
		      (unwind-protect
			 (begin
			    ;(print "using continuation for "
			    ;   (threadless-actor-name actor))
			    (set! scheduled? #t)
			    (continuation msg)
			    (set! scheduled? #f)
			    (set! continuation #unspecified))
			 (current-threadless-actor-set! curr-actor))))
		(concurrent-queue-enqueue! mailbox msg))))))

(define (threadless-actor-receive-w/cont actor cont)
   (with-access::%threadless-actor actor (mailbox mutex continuation)
        (with-recursive-lock mutex
	   (lambda ()
	      (if (not (concurrent-queue-empty? mailbox))
		  (let ((msg (concurrent-queue-dequeue! mailbox)))
		     (cont msg))
		  (begin
		     ;(print "setting continuation for "
			;(threadless-actor-name actor))
		     (set! continuation (lambda (msg)
					   (current-threadless-actor-set! actor)
					   (cont msg)))))))
	(raise 'suspended-actor)))

(define (threadless-actor-start! actor)
   (let ((actor::%threadless-actor actor))
      (scheduler-push! (threadless-actor-scheduler)
	 (lambda ()
	    (with-handler (lambda (e) (if (eq? e 'suspended-actor)
					  #unspecified
					  (raise e)))
			  ((-> actor body)))))))


;;;; test

; (define (make-abody)
;    (lambda ()
;       (let loop ((val 0))
; 	 (print "Value: " val)
; 	 (threadless-actor-receive-w/cont (current-threadless-actor)
; 	    (lambda (msg)
; 	       (match-case msg
; 		  ((incr)  (loop (+ val 1)))
; 		  ((value ?a) (threadless-actor-send a val)
; 			      (loop val))
; 		  ((lock ?a) (threadless-actor-send a (list 'value))
; 			     (threadless-actor-receive-w/cont
; 				(current-threadless-actor)
; 				(lambda (msg)
; 				   (match-case msg
; 				      ((unlock ?v) (loop v))))))
; 		  (else
; 		   (loop val))))))))

; (define (make-bbody actor)
;    (lambda ()
;       (print "sending incr")
;       (threadless-actor-send actor (list 'incr))
;       (print "sent incr")
;       (print "sending value")
;       (threadless-actor-send actor (list 'value (current-threadless-actor)))
;       (print "sent value")
;       (threadless-actor-receive-w/cont (current-threadless-actor)
; 	 (lambda (msg)
; 	    (print msg)))))

 
; (define (main args)
;    (print (threadless-actor-scheduler))
;    (let* ((a1 (make-threadless-actor (make-abody) 'A1))
; 	  (b1 (make-threadless-actor (make-bbody a1) 'B1)))
;       (print "created actors")
;       (threadless-actor-start! a1)
;       (print "started a1")
;       (threadless-actor-start! b1)
;       (print "started b1")
;       ;(sleep 2000000)
;       (work-queue-finish! (threadless-actor-scheduler))))

	  


	  
      
