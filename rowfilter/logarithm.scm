(define (do-logarithm-filter filename destinationfilename)
   (let* ((image (car (gimp-file-load RUN-NONINTERACTIVE filename filename)))
          (drawable (car (gimp-image-get-active-layer image))))
     (logarithm-filter    RUN-NONINTERACTIVE    image drawable)
     (gimp-file-save RUN-NONINTERACTIVE image drawable destinationfilename destinationfilename)
     (gimp-image-delete image)))

