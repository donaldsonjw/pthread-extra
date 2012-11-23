;;;; Copyright(c) 2010, 2011, 2012 Joseph Donaldson(donaldsonjw@yahoo.com) 
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
   (import concurrent-queue
	   atomics)
   (static
    (class %work-queue-item 
       thunk::procedure
       next::%work-queue-item)
    (class %work-queue
       mutex
       condvar
       max-threads
       idle-threads
       current-threads
       finish
       queue
       ))
   (export (make-work-queue max-threads)
	   (work-queue-finish! queue)
	   (work-queue-push! queue thunk2)
	   (work-queue? queue)
	   (work-queue-empty? queue)))


(define (make-work-queue max-threads)
   (let* ((nwq (instantiate::%work-queue
		 (mutex (make-mutex))
		 (condvar (make-condition-variable))
		 (max-threads max-threads)
		 (idle-threads (instantiate::atomic-int (val 0)))
		 (current-threads (instantiate::atomic-int (val 0)))
		 (finish (instantiate::atomic-boolean (val #f)))
		 (queue (make-concurrent-queue)))))
      nwq))


(define (work-queue? queue)
   (isa?  queue %work-queue))

(define (work-queue-empty? queue)
   (with-access::%work-queue queue ((q2 queue))
      (concurrent-queue-empty? q2)))

(define +work-wait-time+ 1000)

(define-inline (idle-threads-inc! queue::%work-queue)
   (with-access::%work-queue queue (idle-threads)
      (let loop ((t (atomic-compare-and-set! idle-threads
		       (atomic-get idle-threads)
		       (+ (atomic-get idle-threads) 1))))
	 (if (not t)
	     (loop (atomic-compare-and-set! idle-threads
		      (atomic-get idle-threads)
		      (+ (atomic-get idle-threads) 1)))))))

(define-inline (idle-threads-dec! queue::%work-queue)
   (with-access::%work-queue queue (idle-threads)
      (let loop ((t (atomic-compare-and-set! idle-threads
			(atomic-get idle-threads)
			(- (atomic-get idle-threads) 1))))
	 (if (not t)
	     (loop (atomic-compare-and-set! idle-threads
		      (atomic-get idle-threads)
		      (- (atomic-get idle-threads) 1)))))))

(define-inline (idle-threads queue::%work-queue)
   (with-access::%work-queue queue (idle-threads)
      (atomic-get idle-threads)))


(define-inline (current-threads-inc! queue::%work-queue)
   (with-access::%work-queue queue (current-threads)
      (let loop ((t (atomic-compare-and-set! current-threads
		       (atomic-get current-threads)
		       (+ (atomic-get current-threads) 1))))
	 (if (not t)
	     (loop (atomic-compare-and-set! current-threads
		      (atomic-get current-threads)
		      (+ (atomic-get current-threads) 1)))))))

(define-inline (current-threads-dec! queue::%work-queue)
   (with-access::%work-queue queue (current-threads)
      (let loop ((t (atomic-compare-and-set! current-threads
			(atomic-get current-threads)
			(- (atomic-get current-threads) 1))))
	 (if (not t)
	     (loop (atomic-compare-and-set! current-threads
		      (atomic-get current-threads)
		      (- (atomic-get current-threads) 1)))))
      (atomic-get current-threads)))

(define-inline (current-threads queue::%work-queue)
   (with-access::%work-queue queue (current-threads)
      (atomic-get current-threads)))

(define-inline (finish queue)
   (with-access::%work-queue queue (finish)
	    (atomic-get finish)))

(define-inline (finish-set! queue b)
   (with-access::%work-queue queue (finish)
      (let loop ((t (atomic-compare-and-set! finish
			(atomic-get finish)
			b)))
	 (if (not t)
	     (loop (atomic-compare-and-set! finish
		      (atomic-get finish)
		      b))))))

(define (make-work-queue-thread-thunk queue::%work-queue)
   (define (wait-for-work queue::%work-queue)
      ;; indicate we have an idle thread
      (idle-threads-inc! queue)
      (with-handler (lambda (e)
		       (if (isa? e &concurrent-queue-timeout-error)
			   (begin
			      (idle-threads-dec! queue)
			      #f)
			   (raise e)))
		    
		    (let ((res (concurrent-queue-dequeue!
				  (-> queue queue)
				  +work-wait-time+)))
		       (idle-threads-dec! queue)
		       res)))
							
   (lambda ()
      (current-threads-inc! queue)
      (let loop ((thunk2 (wait-for-work queue)))
	 (when thunk2 
	    (thunk2)
	    (loop (wait-for-work queue))))
      
      ;; signal we are done
      (let ((ct (current-threads-dec! queue)))
	 ;(fprint (current-error-port) "current threads is ct:" ct)
	 ;(fprint (current-error-port) "finish: " (finish queue))
	 (when (and (finish queue)
		    (<=  ct 0))
	    (condition-variable-signal! (-> queue condvar))))))
			 
			 
		      		     
(define (work-queue-finish! queue)
   (let ((queue::%work-queue queue))
      (synchronize (-> queue mutex)
	 (finish-set! queue #t)
	 (let loop ((ct (current-threads queue)))
	    (when (> ct  0)
	       ;(fprint (current-error-port) "in finish! current threads is ct:" ct)
	       (when (not (condition-variable-wait! (-> queue condvar)
			     (-> queue mutex) 1000))
		  (loop (current-threads queue))))))))


(define (work-queue-push! queue thunk2)
   (let ((q::%work-queue queue))
      (with-access::%work-queue queue ((q2 queue)
				       max-threads)
	 (concurrent-queue-enqueue! q2 thunk2)
	 (when (and (= (idle-threads queue) 0)
		    (< (current-threads queue) max-threads))
	    (thread-start!
	       (instantiate::pthread
		  (body (make-work-queue-thread-thunk queue))))))))
   
	       

#;(define (main args)
   (let ((work-queue (make-work-queue 6)))
      (do ((i 0 (+ i 1)))
	  ((= i 3000))
	  ;(print work-queue)
	  (work-queue-push! work-queue
	     (lambda ()									(print (format "~a: " (current-thread)) i "\n")
		     (flush-output-port
			(current-output-port))     
		     )))
      
      (work-queue-finish! work-queue)
      ;(print work-queue)
      ))


