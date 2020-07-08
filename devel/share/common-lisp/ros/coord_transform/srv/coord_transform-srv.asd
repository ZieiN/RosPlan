
(cl:in-package :asdf)

(defsystem "coord_transform-srv"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
               :nav_msgs-msg
)
  :components ((:file "_package")
    (:file "coords" :depends-on ("_package_coords"))
    (:file "_package_coords" :depends-on ("_package"))
  ))