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
(module atomics
   (library pthread)
   (export
      (abstract-class atomic)
      (final-class atomic-boolean::atomic
	 (val::bbool (default #f)))
      (final-class atomic-int::atomic
	 (val::bint (default 0)))
      (final-class atomic-long::atomic
	 (val::belong (default 0)))
      (final-class atomic-llong::atomic
	 (val::bllong (default 0)))
      (final-class atomic-obj::atomic
	 val)
      
      (generic atomic-compare-and-set! a::atomic expect update)
      (generic atomic-get a::atomic)
      (generic atomic-get-and-set! a::atomic val)
      (generic atomic-set! a::atomic val)))

;;;; atomic protocol
(define-generic (atomic-compare-and-set! a::atomic expect update))
(define-generic (atomic-get a::atomic))
(define-generic (atomic-get-and-set! a::atomic val))
(define-generic (atomic-set! a::atomic val))


;;;; atomic booleans

;;; helper to convert to boolean
(define-inline  (boolean<- val)
   (if val #t #f))

(define-method (atomic-compare-and-set! a::atomic-boolean expect update)
   (let ((e::bbool (boolean<- expect))
	 (u::bbool (boolean<- update)))
   (pragma::bool "__sync_bool_compare_and_swap((long*)&$1,(long)$2, (long)$3)"
      (-> a val)
      e
      u)))


(define-method (atomic-get a::atomic-boolean)
   (-> a val))

(define-method (atomic-get-and-set! a::atomic-boolean val)
   (let ((v::bbool (boolean<- val)))
   (pragma::bool "__sync_lock_test_and_set((long*)&$1,(long)$2)"
      (-> a val)
      v)))

(define-method (atomic-set! a::atomic-boolean val)
   (let ((v::bbool (boolean<- val)))
   (pragma::bool "__sync_lock_test_and_set((long*)&$1,(long)$2)"
      (-> a val)
      v)
   #unspecified))



;;;; atomic ints

(define-method (atomic-compare-and-set! a::atomic-int expect update)
   (let ((e::bint expect)
	 (u::bint update))
   (pragma::bool "__sync_bool_compare_and_swap((long*)&$1,(long)$2, (long)$3)"
      (-> a val)
      e
      u)))


(define-method (atomic-get a::atomic-int)
   (-> a val))

(define-method (atomic-get-and-set! a::atomic-int val)
   (let* ((v::bint val))
      (pragma::bint "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
	 (-> a val)
	 v)))

(define-method (atomic-set! a::atomic-int val)
   (let ((v::bint val))
   (pragma::bint "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
      (-> a val)
      v)
   #unspecified))


;;;; atomic long
(define-method (atomic-compare-and-set! a::atomic-long expect update)
   (let ((e::belong expect)
	 (u::belong update))
   (pragma::bool "__sync_bool_compare_and_swap((long*)&$1,(long)$2, (long)$3)"
      (-> a val)
      e
      u)))


(define-method (atomic-get a::atomic-long)
   (-> a val))

(define-method (atomic-get-and-set! a::atomic-long val)
   (let* ((v::belong val))
      (pragma::belong "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
	 (-> a val)
	 v)))

(define-method (atomic-set! a::atomic-long val)
   (let ((v::belong val))
   (pragma::belong "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
      (-> a val)
      v)
   #unspecified))


;;;; atomic llong
(define-method (atomic-compare-and-set! a::atomic-llong expect update)
   (let ((e::bllong expect)
	 (u::bllong update))
   (pragma::bool "__sync_bool_compare_and_swap((long*)&$1,(long)$2, (long)$3)"
      (-> a val)
      e
      u)))


(define-method (atomic-get a::atomic-llong)
   (-> a val))

(define-method (atomic-get-and-set! a::atomic-llong val)
   (let* ((v::bllong val))
      (pragma::bllong "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
	 (-> a val)
	 v)))

(define-method (atomic-set! a::atomic-llong val)
   (let ((v::bllong val))
   (pragma::bllong "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
      (-> a val)
      v)
   #unspecified))


;;;; atomic obj
(define-method (atomic-compare-and-set! a::atomic-obj expect update)
   (let ((e::obj expect)
	 (u::obj update))
   (pragma::bool "__sync_bool_compare_and_swap((long*)&$1,(long)$2, (long)$3)"
      (-> a val)
      e
      u)))


(define-method (atomic-get a::atomic-obj)
   (-> a val))

(define-method (atomic-get-and-set! a::atomic-obj val)
   (let* ((v::obj val))
      (pragma::obj "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
	 (-> a val)
	 v)))

(define-method (atomic-set! a::atomic-obj val)
   (let ((v::obj val))
   (pragma::obj "(obj_t)__sync_lock_test_and_set((long*)&$1,(long)$2)"
      (-> a val)
      v)
   #unspecified))




; (let ((bt (instantiate::atomic-boolean (val #t)))
;       (bi (instantiate::atomic-int (val 2)))
;       (li (instantiate::atomic-obj (val #l4))))
;    (print "boolean current value: " (atomic-get bt))
;    (print "try boolean atomic-compare-and-set!: " (atomic-compare-and-set! bt 'dog 'cat ))
;    (print "int current value: " (atomic-get bi))
;    (print "try int atomic-compare-and-set!: " (atomic-compare-and-set! bi 2 4 ))

;    (print "llong current value: " (atomic-get li))
;    (print "try llong atomic-compare-and-set!: " (atomic-compare-and-set! li #l4 'dog ))
;    (print "llong current value: " (atomic-get li))
;    )