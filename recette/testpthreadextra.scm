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
(module testpthreadextra
   (library pthread-extra)
   (main main))


(define (ping-pong-message? msg)
   (and (list? msg)
	(eq? (car msg) 'ping-pong)))

(define (ping-pong-body msg)
   (caddr msg))

(define (ping-pong-sender msg)
   (cadr msg))

(define (make-ping-pong-message action)
   (list 'ping-pong (current-actor) action))

(define (make-pong-action ping count)
   (lambda ()
      (actor-send ping
		    (make-ping-pong-message 'pong))
   (let loop ((msg (actor-receive (current-actor)))
	      (remaining count))
      (if (ping-pong-message? msg)
	  (let ((body (ping-pong-body msg)))
	     (case body
		((ping)
		 (print "Pong:  ping with " remaining " remaining")
		 (if (> remaining 0)
		     (begin
			(actor-send ping
			   (make-ping-pong-message 'pong))
			(loop (actor-receive (current-actor))
			   (- remaining 1)))
		     (actor-send ping
			(make-ping-pong-message 'exit))))
		(else
		 #unspecified)))))))

(define (ping-action)
   (let loop ((msg (actor-receive (current-actor))))
      (if (ping-pong-message? msg)
	  (let ((body (ping-pong-body msg)))
	     (case body
		((pong)
		 (print "Ping:  pong")
		 (actor-send (ping-pong-sender msg)
		    (make-ping-pong-message 'ping)) 
		 (loop (actor-receive (current-actor))))
		(else
		 #unspecified))))))

(define (main args)
   (let ((wq (make-work-queue 6)))
      (work-queue-finish! wq))

   (let* ((ping-actor (make-actor ping-action))
	  (pong-actor (make-actor (make-pong-action ping-actor 10))))
      (actor-start-joinable! ping-actor)
      (actor-start-joinable! pong-actor)
      (actor-join! ping-actor)
      (actor-join! pong-actor)
     ))