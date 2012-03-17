;;;; Copyright(c) 2010, 2011 Joseph Donaldson(donaldsonjw@yahoo.com) 
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


;;;; This is a work-queue implementation modeled after the one described in
;;;; David Butenhof's Programming with POSIX Threads
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
	   (work-queue-push! queue thunk2)
	   (work-queue? queue)
	   (work-queue-empty? queue)))


(define (make-work-queue max-threads)
   (let* ((nwq (instantiate::%work-queue
		 (max-threads max-threads)
		 (idle-threads 0)
		 (current-threads 0)
		 (finish #f)
		 (mutex (make-mutex))
		 (condition-variable (make-condition-variable))
		 (first (class-nil %work-queue-item))
		 (last (class-nil %work-queue-item)))))
      nwq))


(define (work-queue? queue)
   (isa?  queue %work-queue))

(define (work-queue-empty? queue)
   (with-access::%work-queue queue (first last)
      (eq? first (class-nil %work-queue-item))))

(define +work-wait-time+ 60000)

(define (make-work-queue-thread-thunk queue::%work-queue)
   (define (wait-for-work queue::%work-queue)
      (let loop ((empty? (work-queue-empty? queue)))
	 (if (and empty? (not (-> queue finish )))
	     (begin
		;; indicate we have an idle thread
		(set! (-> queue idle-threads )
		   (+ (-> queue idle-threads ) 1))
		(let ((res (condition-variable-wait!
			      (-> queue condition-variable)
			      (-> queue mutex )
			      +work-wait-time+)))
		   (if (not res)
		       (begin
			  (set!
			     (-> queue idle-threads)
			     (- (-> queue idle-threads) 1))
			  #f)
		       (begin
			  (set! (-> queue idle-threads)
			     (- (-> queue idle-threads) 1))
			  (loop (work-queue-empty? queue))))))
	     (if (not empty?)
		 #t
		 #f))))
		 
   (lambda ()
      (with-lock (-> queue mutex )
            (lambda ()
	       (let loop ((finish (-> queue finish )))
		  (when (wait-for-work queue)
		     (let ((thunk2 (%work-queue-pop! queue)))
			(mutex-unlock! (-> queue mutex ))
			(thunk2)
			(mutex-lock! (-> queue mutex )))
		     (loop (-> queue finish ))))
	       ;(flush-output-port (current-output-port))
	       (set!
		(-> queue current-threads)
		(- (-> queue current-threads) 1))
	       (when (= (-> queue current-threads) 0)
		  (condition-variable-signal! (-> queue condition-variable)))
	       ))))
			 
			 
		      		     
(define (work-queue-finish! queue)
   (let ((queue::%work-queue queue))
      (with-lock (-> queue mutex)
	 (lambda ()
	    (set! (-> queue finish) #t)
	    (condition-variable-broadcast! (-> queue condition-variable))
	    (let loop ((rt (-> queue current-threads)))
	       (when (> rt 0)
		  (condition-variable-wait! (-> queue condition-variable )
		     (-> queue mutex))
		  (loop (-> queue current-threads))))))))

(define (work-queue-push! queue thunk2)
   (let ((q::%work-queue queue))
      (with-access::%work-queue queue (mutex
					 condition-variable
					 first
					 last
					 current-threads
					 idle-threads
					 max-threads)
	 (let ((nwi (instantiate::%work-queue-item
		       (thunk thunk2)
		       (next (class-nil %work-queue-item)))))
	    (with-lock mutex
	       (lambda ()
		  (if (work-queue-empty? q)
		      (begin
			 (set! first nwi)
			 (set! last nwi))
		      (begin
			 (set! (-> q last next)
			    nwi)
			 (set! last nwi)))
		  (flush-output-port (current-output-port))
		  (if (> idle-threads 0)
		      (condition-variable-signal! condition-variable)
		      (when (< current-threads max-threads)
			 (thread-start!
			    (instantiate::pthread
			       (body (make-work-queue-thread-thunk queue))))
			 (set! current-threads (+ current-threads 1))))))))))
   
	       
		   
;;; assumes the mutex used to protect the queue has already been obtained
(define (%work-queue-pop! queue::%work-queue)
   (with-access::%work-queue queue (first)
      (let ((item::%work-queue-item first))
	 (set! first (-> item next ))
	 (->  item thunk))))


   


#;(define (main args)
   (let ((work-queue (make-work-queue 6)))
      (work-queue-empty? work-queue)
      (print (%work-queue-item-thunk (class-nil %work-queue-item)))
      (do ((i 0 (+ i 1)))
	  ((= i 3000))
	  ;(print work-queue)
	  (work-queue-push! work-queue (lambda ()									(print (format "~a: " (thread-name (current-thread))) i)
															       (flush-output-port
																(current-output-port))     
					  )))

      (work-queue-finish! work-queue)
   ;(print work-queue)
      ))


