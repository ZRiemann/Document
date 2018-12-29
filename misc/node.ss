;;; router
'(self
  (id . "R2")
  (domain . "D0")
  (route-point TCP 8240)
  (web-point 80 TCP 80)
  (device-point 9090 UDP 9090))
;;; router
'((self
   (id . "R1")
   (domain . "D1")
   (route-point TCP 8240))
  (remote "192.168.10.246" TCP 8240)
  (remote "192.168.10.248" TCP 8240))
;;; leaf
'((self
   (id . "L1")
   ;;共享路由节点的domain
   )
  (remote "192.168.10.247" TCP 8240))
;;; anonymous
;;; 只需要知道对端节点
'(remote "192.168.10.247" TCP 8240)
;;; S表达式C解析器
;;; s_expression.h
