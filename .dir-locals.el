(("content-org/"
  . ((org-mode . ((eval . (progn
                           (org-hugo-auto-export-mode)
                           (let ((local-project-root (and (fboundp '+project-root)
                                                          (+project-root))))
                             (when (and local-project-root buffer-file-name)
                               (setq-local org-download-image-dir
                                           (expand-file-name (concat "static/"
                                                   (file-relative-name buffer-file-name
                                                                       local-project-root)) local-project-root)))))))))))
