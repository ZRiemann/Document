;; ~/.custom.el
;; file-truename MUST be used!
;;(add-to-list 'exec-path "/var/work/weipzhu/slink/bin")
;;(setenv "PATH" "$PATH:/var/work/weipzhu/slink/bin" t)

(setenv "GTAGSLIBPATH" (concat "/usr/include"
                               ":"
                               "/var/work/weipzhu/slink/gtags-obj/usr/lib/gcc/x86_64-redhat-linux/4.8.2/include"
                               ":"
                               "/var/work/weipzhu/slink/gtags-obj/usr/local/include"
                               ":"
                               (file-truename "/var/work/weipzhu/workspaces/5g-layer-1")))
(setenv "MAKEOBJDIRPREFIX" (file-truename "/var/work/weipzhu/slink/gtags-obj"))
(setq company-backends '((company-dabbrev-code company-gtags)))


;; ggtags mode for c/c++
(require 'ggtags)
(add-hook 'c-mode-common-hook
          (lambda ()
            (when (derived-mode-p 'c-mode 'c++-mode 'java-mode)
              (ggtags-mode 1))))
(provide 'init-ggtags)
;; open all org file with indent mode
;; (setq org-startup-indented t)

;; iimage mode
(autoload 'iimage-mode "iimage" "Support Inline image minor mode." t)
(autoload 'turn-on-iimage-mode "iimage" "Turn on Inline image minor mode." t)

;; load-theme zenburn
(load-theme 'tango-dark t)
;; start a shell
(shell)

;; set tab width
;;(setq default-tab-width 8)
;;(setq indent-tabs-mode nil)

