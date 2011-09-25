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

;;;; a barrier class modeled off the one provided in Java's
;;;; java.util.concurrent.CyclicBarrier class

(module barrier
   (library pthread)
   (static (class %barrier
	      (mutex (default (make-mutex)))
	      (cond-var (default (make-condition-variable)))
	      (cycle (default 0))
	      (current (default 0))
	      (broken? (default #f))
	      parties
	      action))
   
   (export (class &barrier-timeout-error::&error)
	   (class &barrier-broken-error::&error)
	   (make-barrier parties #!optional (action (lambda () #unspecified)))
	   (barrier-wait! barrier #!optional (timeout::long 0))
	   (barrier-parties barrier)
	   (barrier-get-number-waiting barrier)
	   (barrier? barrier)))


(define (barrier? barrier)
   (%barrier? barrier))



(define (make-barrier parties #!optional (action (lambda () #unspecified)))
   (instantiate::%barrier (parties parties)
			  (action action)))

(define (barrier-wait! barrier #!optional (timeout::long 0))
   (with-access::%barrier barrier (mutex cond-var cycle current parties action
				     broken?)
      (with-lock mutex
	 (lambda ()
	    (let ((my-cycle cycle))
	       (set! current (+ current 1))
	       (let ((my-index current))
		  (let loop ()
		     (cond (broken?
			      (raise (instantiate::&barrier-broken-error
					(proc "barrier-wait!")
					(msg "barrier broken!")
					(obj barrier))))
			    ((and (= current parties)
				 (= my-cycle cycle))
			    (set! cycle (+ cycle 1))
			    (set! current 0)
			    (action)
			    (condition-variable-broadcast! cond-var)
			    my-index)
			   ((= my-cycle cycle)
			    (if (condition-variable-wait! cond-var mutex
				   timeout)
				(loop)
				(begin
				   (set! broken? #t)
				   (condition-variable-broadcast! cond-var)
				   (raise (instantiate::&barrier-timeout-error
					     (proc "barrier-wait!")
					     (msg  "barrier-wait! timed out")
					     (obj barrier))))))
			   (else
			    my-index)))))))))

(define (barrier-parties barrier)
   (%barrier-parties barrier))


(define (barrier-get-number-waiting barrier)
   (with-access::%barrier barrier (mutex current)
      (with-lock mutex
	(lambda ()  current))))


;; testing
#;(define (main args)
   (let* ((barrier (make-barrier 3 (lambda () (print "action called"))))
	  (threads 
	     (do ((i 0 (+ i 1))
		  (res '() (cons (instantiate::pthread
				    (body (lambda () (print "thread: " i)
						  (with-handler
						     (lambda (e)
							(if (or (&barrier-timout-error? e)
								(&barrier-broken-error? e))
							    (print "exception caught: " i)
							    (raise e)))
						     (when (not (= i 0))
							(thread-sleep! 2000000))
						     (barrier-wait! barrier (if (= i 0) 1000 0)))))) res)))
		 ((= i 3) res))))
      (print "number of threads: " (length threads))
      (print "currently waiting on barrier: "
	 (barrier-get-number-waiting barrier))
      (for-each (lambda (t) (thread-start-joinable! t)) threads)
      (for-each (lambda (t) (thread-join! t)) threads)))
