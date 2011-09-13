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

(module semaphore
   (static
    (class %semaphore
       (permits (default 0))
       (mutex (default (make-mutex)))
       (cond-var (default (make-condition-variable)))))
   (export (semaphore-signal! sem #!optional (count 1))
	   (semaphore-wait! sem #!optional (timeout::long 0))
	   (make-semaphore permits)))


(define (make-semaphore permits)
   (instantiate::%semaphore (permits permits)))

(define (semaphore-wait! sem #!optional (timeout::long 0))
   (with-access::%semaphore sem (mutex cond-var permits)
      (with-lock mutex
	 (lambda ()
	    (let loop ()
	       (if (<= permits 0)
		   (if (condition-variable-wait! cond-var mutex timeout)
		       (loop)
		       #f)
		   (begin (set! permits (- permits 1))
			  #t)
		   ))))))
 

(define (semaphore-signal! sem #!optional (count 1))
   (with-access::%semaphore sem (mutex cond-var permits)
      (with-lock mutex
	 (lambda ()
	    (set! permits (+ permits count))
	    (condition-variable-signal! cond-var)))))


   