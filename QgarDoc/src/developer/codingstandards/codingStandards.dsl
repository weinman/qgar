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

;;
;; FILENAME
;;
(define %root-filename%
  ;; Name for the root HTML document
  "codingStandards")

(define %html-prefix% 
  ;; Add the specified prefix to HTML output filenames
    "codingStandards_")

(define %html-ext% 
  ;; Default extension for HTML output files
  ".html")

    

;;
;; CSS STYLESHEETS
;;

(define %stylesheet%
  ;; Name of the stylesheet to use
  "codingStandards.css")

(define %stylesheet-type%
  ;; The type of the stylesheet to use
  "text/css")

(define %css-decoration%
  ;; Enable CSS decoration of elements
  #t)

(define %body-attr% 
  ;; No attributes should be defined in body. They'll be set in the attached CSS
  (list))



;;
;; TOC & NAVIGATION
;;

(define %section-autolabel%
  ;; Are sections enumerated?
  #f)

(define %header-navigation%
  ;; Should navigation links be added to the top of each page?
  #t)

(define %footer-navigation%
  ;; Should navigation links be added to the bottom of each page?
  #t)

(define %generate-article-toc% 
  ;; Should a Table of Contents be produced for Articles?
  #t)



;;
;; ADMONITION GRAPHICS
;;

(define %admon-graphics%
  ;; Use graphics in admonitions?
  #t)

(define %admon-graphics-path%
  ;; Path to admonition graphics
  "./stylesheet-images/")

</style-specification-body>
</style-specification>
<external-specification id="docbook" document="docbook.dsl">
</style-sheet>
