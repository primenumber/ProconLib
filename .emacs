(setq backup-inhibited t)
(setq auto-save-default nil)

(column-number-mode t)
(setq-default tab-width 2 indent-tabs-mode nil)

(global-set-key "\C-h" 'delete-backward-char)

(setq indent-line-function 'indent-relative-maybe)
(global-set-key "\C-m" 'newline-and-indent)
(global-set-key (kbd "C-/") 'undo)
