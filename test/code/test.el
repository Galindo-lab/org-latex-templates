(setq org-latex-caption-above nil)

(use-package modus-themes
  :config
  ;; (load-theme 'modus-operandi t)
  (load-theme 'modus-vivendi t)
  )

(defun reverse-region (beg end)
  "Reverse characters between BEG and END."
  (interactive "r")
  (let ((region (buffer-substring beg end)))
    (delete-region beg end)
    (insert (nreverse region))))
