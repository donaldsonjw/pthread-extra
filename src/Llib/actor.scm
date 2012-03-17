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

(module actor
   (import concurrent-queue)
   (library pthread)
   (export
    (class &actor-receive-timeout-error::&error)
    (actor-send actor msg)
    (actor-receive actor #!optional (timeout::long 0))
    (make-actor body #!optional (name (gensym 'actor)))
    (inline actor-start! actor)
    (inline actor-start-joinable! actor)
    (inline actor-join! actor)
    (inline current-actor)
    (actor? actor))
   (static (class %actor::pthread
	      (mailbox (default (make-concurrent-queue))))))



(define (make-actor body #!optional (name (gensym 'actor)))
   (instantiate::%actor (body body) (name name)))

(define (actor? actor)
   (isa? actor %actor))

(define-inline (current-actor)
   (let ((t (current-thread)))
      (if (actor? t)
	  t
	  #unspecified)))

(define-inline (actor-start! actor)
   (thread-start! actor))

(define-inline (actor-start-joinable! actor)
   (thread-start-joinable! actor))

(define-inline (actor-join! actor)
   (thread-join! actor))

(define (actor-send actor msg)
   (with-access::%actor actor (mailbox)
      (concurrent-queue-enqueue! mailbox msg)))

(define (actor-mailbox actor)
   (let ((actor::%actor actor))
      (-> actor mailbox)))

(define (actor-receive actor #!optional (timeout::long 0))
   (with-handler (lambda (e)
		    (if (isa? e &concurrent-queue-timeout-error)
			(raise (instantiate::&actor-receive-timeout-error
				  (proc "actor-receive")
				  (msg "actor-receive timed out")
				  (obj actor)))
			(raise e)))
		 (with-access::%actor actor (mailbox)
		       (concurrent-queue-dequeue! mailbox timeout))))


