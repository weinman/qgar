<!DOCTYPE style-sheet PUBLIC "-//James Clark//DTD DSSSL Style Sheet//EN" [
<!ENTITY % html "IGNORE">
<![%html;[
<!ENTITY % print "IGNORE">
<!ENTITY docbook.dsl PUBLIC "-//Norman Walsh//DOCUMENT DocBook HTML Stylesheet//EN" CDATA dsssl>
]]>
<!ENTITY % print "INCLUDE">
<![%print;[
<!ENTITY docbook.dsl PUBLIC "-//Norman Walsh//DOCUMENT DocBook Print Stylesheet//EN" CDATA dsssl>
]]>
]>
<style-sheet>
<style-specification id="print" use="docbook">
<style-specification-body> 

;; customize the print stylesheet

(define %paper-type%
  ;; Name of paper type
  "A4")


(define %generate-heading-level%   
  ;; Output RTF heading level characteristics?
  #t)

; === Title page ===

(define %generate-article-titlepage% 
  ;; Should an article title page be produced?
  #t)

(define %generate-article-titlepage-on-separate-page%
  ;; Should the article title page be on a separate page?
  #t)

; === TOC ===

(define %generate-article-toc% 
  ;; Should a Table of Contents be produced for Articles?
  #t)

(define %generate-article-toc-on-titlepage%
  ;; Should the Article TOC appear on the Article title page?
  #t)

; === Sections ===

(define %section-autolabel% 
  ;; Are sections enumerated?
  #t)

(define %body-start-indent% 
  ;; Default indent of body text
  0pi)

(define %block-start-indent% 
  ;; Extra start-indent for block-elements
  1pi)



</style-specification-body>
</style-specification>
<style-specification id="html" use="docbook">
<style-specification-body> 

;; customize the html stylesheet

(define %chapter-autolabel% #t)
(define %section-autolabel% #t)
(define (toc-depth nd) 2)

; === File names ===
(define %root-filename% "compilationGuide");; name for the root html file
(define %html-ext% ".html")             ;; default extension for html output files
(define %html-prefix% "ig")               ;; prefix for all filenames generated (except root)
(define %use-id-as-filename% #f)        ;; if #t uses ID value, if present, as filename
                                        ;;   otherwise a code is used to indicate level
                                        ;;   of chunk, and general element number
                                        ;;   (nth element in the document)
(define use-output-dir #f)              ;; output in separate directory?
(define %output-dir% "HTML")            ;; if output in directory, it's called HTML

; === HTML settings ===
(define %html-pubid% "-//W3C//DTD HTML 4.01 Transitional//EN") ;; Nearly true :-(
(define %html40% #t)

; === STYLESHEET
(define %stylesheet%
  ;; Name of the stylesheet to use
  "compilationGuide.css")

; === Media objects ===
(define preferred-mediaobject-extensions  ;; this magic allows to use different graphical
  (list "png" "jpg" "jpeg"))            ;;   formats for printing and putting online
(define acceptable-mediaobject-extensions
  (list "bmp" "gif" "eps" "epsf" "avi" "mpg" "mpeg" "qt"))
(define preferred-mediaobject-notations
  (list "PNG" "JPG" "JPEG"))
(define acceptable-mediaobject-notations
  (list "EPS" "BMP" "GIF" "linespecific"))                                                                                                    
; === Rendering ===
(define %admon-graphics% #f)            ;; use symbols for Caution|Important|Note|Tip|Warning

; === Books only ===
(define %generate-book-titlepage% #t)
(define %generate-book-toc% #t)
(define ($generate-chapter-toc$) #f)    ;; never generate a chapter TOC in books

; === Articles only ===
(define %generate-article-titlepage% #t)
(define %generate-article-toc% #t)      ;; make TOC


</style-specification-body>
</style-specification>
<external-specification id="docbook" document="docbook.dsl">
</style-sheet>


