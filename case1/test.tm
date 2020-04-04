#Q = {q0,q1,q_lnew,q_add,q_check,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}
#S = {0}
#G = {0,a,b,n,_,T,r,u,e,F,a,l,s}
#q0 = q0
#B = _
#F {halt_accept}
#N = 1

;State q0:begin
q0 _ _ l accept
q0 0 a r q1

;State q1:one zero
q1 _ _ l accept
q1 0 b r q_check

;State q_check:check if accept
q_check _ _ l accept
q_check 0 0 l q_lnew
q_check n b r q_check
q_check b a r q_check

;State q_lnew:add the a's number to the final position , trans to n
q_lnew _ _ r q_check
q_lnew * * l q_lnew
q_lnew a b r q_add

;State q_add
q_add _ _ l reject
q_add 0 n l q_lnew
q_add * * r q_add

;State accept
accept * _ l accept
accept _ T r accept2
accept2 _ r r accept3
accept3 _ u r accept4
accept4 _ e * halt_accept

;State reject
reject * _ l reject
reject _ F r reject2
reject2 _ a r reject3
reject3 _ l r reject4
reject4 _ s r reject5
reject5 _ e * halt_reject

