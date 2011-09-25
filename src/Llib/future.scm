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

(module future
   (library pthread)
   (export (class &future-timeout-error::&error)
	   (future? future))
   (static (class %future
	      (mutex (default (make-mutex)))
	      (cond-var (default (make-condition-variable)))
	      (thread (default #unspecified))
	      (done (default #f))
	      (result (default #unspecified))))
   (export (make-future thunk)
	   (future-touch future #!optional (timeout::long 0))))

(define (make-future-thread future thunk)
   (define (make-future-thunk future thunk)
      (lambda ()
	 (with-access::%future future (mutex cond-var done result)
	    (let ((res (thunk)))
	       (with-lock mutex
		  (lambda ()
		     (set! done #t)
		     (set! result res)
		     (condition-variable-broadcast! cond-var)))))))
   (instantiate::pthread (body (make-future-thunk future thunk))))
			

(define (future? future)
   (%future? future))

(define (make-future thunk)
   (let ((res (instantiate::%future))) 
      (%future-thread-set! res (make-future-thread res thunk))
      (thread-start! (%future-thread res))
      res))


(define (future-touch future #!optional (timeout::long 0))
   (with-access::%future future (mutex cond-var done result)
      (with-lock mutex
	 (lambda ()
	    (let loop ()
	       (if done
		   result
		   (if (condition-variable-wait! cond-var mutex timeout)
		       (loop)
		       (raise (instantiate::&future-timeout-error
				 (proc "future-touch")
				 (msg "future-touch timed out")
				 (obj future))))))))))



#;(define (main args)
   (let ((ft (make-future (lambda () (thread-sleep! 10000000) 5))))
      (print (future-touch ft 11000))))
