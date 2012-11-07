(define (symmetricrange-filter filename destinationfilename)
   (let* ((image (car (gimp-file-load RUN-NONINTERACTIVE filename filename)))
          (drawable (car (gimp-image-get-active-layer image))))
     (plug-in-symmetricrange RUN-NONINTERACTIVE
	                   image drawable)
     (gimp-file-save RUN-NONINTERACTIVE image drawable destinationfilename destinationfilename)
     (gimp-image-delete image)))
