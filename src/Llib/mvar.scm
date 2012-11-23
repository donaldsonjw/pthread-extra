;;;; Copyright(c) 2012 Joseph Donaldson(donaldsonjw@yahoo.com) 
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

;;;; An implementation of MVar as found in Haskell and described in the
;;;; Concurrent Haskell paper

(module mvar
   (library pthread)
   (static
      (class %mvar
	 empty
	 val
	 mutex
	 empty-condvar
	 full-condvar))
   (export (make-mvar #!optional (init-val #unspecified))
	   (mvar-take! m)
	   (mvar-put! m v)
	   (mvar-read m)
	   (mvar-swap! m v)
	   (with-mvar m fun)
	   (mvar-try-take! m)
	   (mvar-try-put! m v)))



(define (make-mvar #!optional (init-val #unspecified))
   (instantiate::%mvar (empty (eq? init-val #unspecified))
		       (val init-val)
		       (mutex (make-mutex))
		       (empty-condvar (make-condition-variable))
		       (full-condvar (make-condition-variable))))

(define (mvar-take! m)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
	 (synchronize mutex
	    (let loop ()
	       (if empty
		   (begin
		      (condition-variable-wait! full-condvar mutex)
		      (loop))
		   (let ((res val))
		      (set! empty #t)
		      (set! val #unspecified)
		      (condition-variable-signal! empty-condvar)
		      res))))))

(define (mvar-put! m v)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
      (synchronize mutex
	 (let loop ()
	    (if empty
		(begin
		   (set! empty #f)
		   (set! val v)
		   (condition-variable-signal! full-condvar))
		(begin
		   (condition-variable-wait! empty-condvar mutex)
		   (loop)))))))


(define (mvar-read m)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
      (synchronize mutex
	 (let loop ()
	    (if empty
		(begin
		   (condition-variable-wait!  full-condvar mutex)
		   (loop))
		(begin
		   (condition-variable-signal! full-condvar)
		   val))))))

(define (mvar-swap! m v)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
      (synchronize mutex
	 (let loop ()
	    (if empty
		(begin
		   (condition-variable-wait!  full-condvar mutex)
		   (loop))
		(begin
		   (let ((res val))
		      (set! val v)
		      (condition-variable-signal! full-condvar)
		      res)))))))


(define (mvar-try-put! m v)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
      (synchronize mutex
	 (if empty
	     (begin
		(set! empty #f)
		(set! val v)
		(condition-variable-signal! full-condvar))
	     #f))))

(define (mvar-try-take! m)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
	 (synchronize mutex
	    (if empty
		(values #f #unspecified)
		(let ((res val))
		   (set! empty #t)
		   (set! val #unspecified)
		   (condition-variable-signal! empty-condvar)
		   (values #t res))))))

(define (with-mvar m fun)
   (with-access::%mvar m (mutex full-condvar empty-condvar empty val)
      (synchronize  mutex
	 (with-handler (lambda (e)
			  ;; with-mvar was unsuccessful
			  ;; signal that the value was not consumed
			  ;; and reraise the exception
			  (condition-variable-wait!  full-condvar mutex)
			  (raise e))
		       (let loop ()
			  (if empty
			      (begin
				 (condition-variable-wait!  full-condvar mutex)
				 (loop))
			      (begin
				 (let ((res (fun val)))
				    (set! empty #t)
				    (set! val #unspecified)
				    (condition-variable-signal! empty-condvar)
				    res))))))))


; (define (main args)
; (let* ((m (make-mvar))
;        (t1 (instantiate::pthread (body (lambda () (let loop ((i 0))
; 						  (mvar-put! m i)
; 						  (if (< i 1000)
; 						      (loop (+ i 1))))))))
;        (t2 (instantiate::pthread (body (lambda () (let loop ()
; 						  (let ((v (mvar-take! m)))
; 						     (print "v : " v)
; 						     (if (not (= v 999))
; 							 (loop)))))))))
;    (thread-start-joinable! t1)
;    (thread-start-joinable! t2)
;    (thread-join! t1)
;    (thread-join! t2)))


						  