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

(module concurrent-queue
   (library pthread)
   (export (class &concurrent-queue-timeout-error::&error)
	   (make-concurrent-queue)
	   (concurrent-queue-enqueue! q item)
	   (concurrent-queue-dequeue! q #!optional (timeout::long 0))
	   (concurrent-queue? q))
   (static
    (class %queue
       first
       last
       (cond-var (default (make-condition-variable)))
       (enqueue-mutex (default (make-mutex)))
       (dequeue-mutex (default (make-mutex))))))



(define (make-concurrent-queue)
   (let ((dummy (cons 'dummy '())))
      (instantiate::%queue (first dummy) (last dummy))))

(define (concurrent-queue? q)
   (%queue? q))

(define (concurrent-queue-enqueue! q item)
   (with-access::%queue q (last enqueue-mutex cond-var)
      (let ((new (cons item '())))
	 (with-lock enqueue-mutex
	    (lambda ()
	       (set-cdr! last new)
	       (set! last new)
	       (condition-variable-signal! cond-var))))))


(define (concurrent-queue-dequeue! q #!optional (timeout::long 0))
   (with-access::%queue q (first dequeue-mutex cond-var)
      (let ((res (with-lock dequeue-mutex
		    (lambda ()
		       (let loop ()
			  (if (pair? (cdr first))
			      (let ((r (cadr first)))
				 (set-car! (cdr first) 'dummy)
				 (set! first (cdr first))
				 r)
			      (if (condition-variable-wait! cond-var
					dequeue-mutex timeout)
				  (loop)
				  (raise (instantiate::&concurrent-queue-timeout-error
					    (proc "concurrent-queue-dequeue!")
					    (msg "concurrent-queue-dequeue! timed out")
					    (obj q))))))))))
	 res)))
			   
			      

; (define (doit name val)
;    (with-output-to-file name
;       (lambda ()
; 	 (print name ": " val))))

; (define (main args)
;    (let ((q (make-concurrent-queue)))

;       (print q)
;       (concurrent-queue-enqueue! q 5)
;       (print q)
;       (print (concurrent-queue-dequeue! q))
;       (print q)
;       (concurrent-queue-enqueue! q 4)
;       (concurrent-queue-enqueue! q 3)
;       (print (concurrent-queue-dequeue! q))
;       ))
      
			   
        