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

;;;; This is a read-write lock implementation modeled after the one described in
;;;; David Butenhof's Programming with POSIX Threads
(module rw-lock
   (library pthread)
   (static
    (class %rw-lock
       (mutex (default (make-mutex)))
       (read-condvar (default (make-condition-variable))) 
       (write-condvar (default (make-condition-variable)))
       (active-readers (default 0))
       (active-writers (default 0))
       (waiting-readers (default 0))
       (waiting-writers (default 0))))
   (export (make-rw-lock)
	   (rw-lock-read-lock! lock)
	   (rw-lock-try-read-lock! lock)
	   (rw-lock-read-unlock! lock)
	   (rw-lock-write-lock! lock)
	   (rw-lock-try-write-lock! lock)
	   (rw-lock-write-unlock! lock)
	   (rw-lock? rw-lock)))

(define (rw-lock? rw-lock)
   (%rw-lock? rw-lock))

(define (make-rw-lock)
   (instantiate::%rw-lock))


(define (rw-lock-read-lock! lock)
   (with-access::%rw-lock lock (mutex read-condvar active-writers
				  waiting-readers active-readers)
      (with-lock mutex
	 (lambda ()
	    (when (> active-writers 0)
	       (set! waiting-readers (+ waiting-readers 1))
	       (unwind-protect
		  (let loop ()
		     (when (> active-writers 0)
			(condition-variable-wait! read-condvar mutex))
		     (loop))
		  (set! waiting-readers (- waiting-readers 1)))       
	    (set! active-readers (+ active-readers 1)))))))


(define (rw-lock-try-read-lock! lock)
   (with-access::%rw-lock lock (mutex  active-writers
				  active-readers)
      (with-lock mutex
	 (lambda ()
	    (if (> active-writers 0)
		#f
		(begin
		   (set! active-readers (+ active-readers 1))
		   #t))))))


(define (rw-lock-read-unlock! lock)
   (with-access::%rw-lock lock (mutex write-condvar active-writers
				  waiting-writers active-readers)
      (with-lock mutex
	 (lambda ()
	    (set! active-readers (- active-readers 1))
	    (when (and (= active-readers 0)
		       (> active-writers 0))
	       (condition-variable-signal! write-condvar))))))

(define (rw-lock-write-lock! lock)
   (with-access::%rw-lock lock (mutex active-writers active-readers
				  write-condvar waiting-writers)
      (with-lock mutex
	 (lambda ()
	    (when (or (> active-readers 0)
		      (> active-writers 0))
	       (set! waiting-writers (+ waiting-writers 1))
	       (unwind-protect
		  (let loop ()
		     (when (or (> active-readers 0)
			       (> active-writers 0))
			(condition-variable-wait! write-condvar mutex))
		     (loop))
		  (set! waiting-writers (- waiting-writers 1))))
	    (set! active-writers (+ active-writers 1))))))

(define (rw-lock-try-write-lock! lock)
   (with-access::%rw-lock lock (mutex active-writers active-readers)
      (with-lock mutex
	 (lambda ()
	    (if (or (> active-readers 0)
		      (> active-writers 0))
		#f
		(begin
		   (set! active-writers (+ active-writers 1))
		   #t))))))

(define (rw-lock-write-unlock! lock)
   (with-access::%rw-lock lock (mutex active-writers waiting-readers waiting-writers read-condvar write-condvar)
      (with-lock mutex
	 (lambda ()
	    (set! active-writers (- active-writers 1))
	    (cond ((> waiting-readers 0)
		   (condition-variable-broadcast! read-condvar))
		  ((> waiting-writers 0))
		   (condition-variable-signal! write-condvar))))))



	    
		   