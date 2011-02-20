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
(module work-queue
   (library pthread)
   (static
    (class %work-queue-item 
       thunk::procedure
       next::%work-queue-item)
    (class %work-queue 
       max-threads
       idle-threads
       current-threads
       finish
       mutex
       condition-variable
       first::%work-queue-item
       last::%work-queue-item
       ))
   (export (make-work-queue max-threads)
	   (work-queue-finish! queue)
	   (work-queue-push! queue thunk2)))


(define (make-work-queue max-threads)
   (let* ((nwq (instantiate::%work-queue
		 (max-threads max-threads)
		 (idle-threads 0)
		 (current-threads 0)
		 (finish #f)
		 (mutex (make-mutex))
		 (condition-variable (make-condition-variable))
		 (first (%work-queue-item-nil))
		 (last (%work-queue-item-nil)))))
      nwq))


(define (work-queue-empty? queue)
   (with-access::%work-queue queue (first last)
      (eq? first (%work-queue-item-nil))))

(define +work-wait-time+ 60000)

(define (make-work-queue-thread-thunk queue)
   (define (wait-for-work queue)
      (let loop ((empty? (work-queue-empty? queue)))
	 (if empty?
	     (begin
		;; indicate we have an idle thread
		(%work-queue-idle-threads-set!
		 queue (+ (%work-queue-idle-threads queue) 1))
		(let ((res (condition-variable-wait!
			  (%work-queue-condition-variable
			   queue)
			  (%work-queue-mutex queue)
			  +work-wait-time+)))
		    (if (not res)
		       (begin
			  (%work-queue-idle-threads-set!
			   queue
			   (- (%work-queue-idle-threads queue) 1))
			  #f)
		       (begin
			  (%work-queue-idle-threads-set!
			   queue (- (%work-queue-idle-threads queue) 1))
			  (loop (work-queue-empty? queue))))))
		#t)))
		 
   (lambda ()
      (with-lock (%work-queue-mutex queue)
            (lambda ()
	       (let loop ((finish (%work-queue-finish queue)))
		  (when (and (not finish)
			     (wait-for-work queue))
		     
		     (let ((thunk2 (%work-queue-pop! queue)))
			(mutex-unlock! (%work-queue-mutex queue))
			(thunk2)
			(mutex-lock! (%work-queue-mutex queue)))
		     (loop (%work-queue-finish queue))))
	       (flush-output-port (current-output-port))
	       (%work-queue-current-threads-set!
		queue
		(- (%work-queue-current-threads queue) 1))
	       ))))
			 
			 
		      		     
(define (work-queue-finish! queue)
   (with-lock (%work-queue-mutex queue)
      (lambda ()
	 (%work-queue-finish-set! queue #t)))
   (let loop ((rt (%work-queue-current-threads queue)))
      (when (> rt 0)
	 (sleep 1000)
	 (loop (%work-queue-current-threads queue)))))

(define (work-queue-push! queue thunk2)
   (with-access::%work-queue queue (mutex
				    condition-variable
				    first
				    last
				    current-threads
				    idle-threads
				    max-threads)
      (let ((nwi (instantiate::%work-queue-item
		    (thunk thunk2)
		    (next (%work-queue-item-nil)))))
	 (with-lock mutex
	    (lambda ()
	       (if (work-queue-empty? queue)
		   (begin
		      (set! first nwi)
		      (set! last nwi))
		   (begin
		      (%work-queue-item-next-set! last
						  nwi)
		      (set! last nwi)))
	       (if (> idle-threads 0)
		   (condition-variable-signal! condition-variable)
		   (when (< current-threads max-threads)
		      (thread-start!
		       (instantiate::pthread
			  (body (make-work-queue-thread-thunk queue))))
		      (set! current-threads (+ current-threads 1)))))))))

	       
		   
;;; assumes the mutex used to protect the queue has already been obtained
(define (%work-queue-pop! queue::%work-queue)
   (with-access::%work-queue queue (first)
      (let ((item first))
	 (set! first (%work-queue-item-next item))
	 (%work-queue-item-thunk item))))


   


#;(define (main args)
   (let ((work-queue (make-work-queue 6)))
      (work-queue-empty? work-queue)
      (print (%work-queue-item-thunk (%work-queue-item-nil)))
      (do ((i 0 (+ i 1)))
	  ((= i 3000))
	;  (print work-queue)
	  (work-queue-push! work-queue (lambda ()									(print (format "~a: " (thread-name (current-thread))) i)
															       (flush-output-port
																(current-output-port))     
					  )))

      (work-queue-finish! work-queue)
      ))
      