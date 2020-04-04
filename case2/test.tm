#Q = {q0,q1,q2,q3,q4,q5,q6,q7,q8,q9,q10,qf,q_lnew,q_add,q_check,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}
#S = {0,1}
#G = {0,1,a,b,z,_,T,r,u,e,F,a,l,s}
#q0 = q0
#B = _
#F {halt_accept}
#N = 1

;State q0:start
q0 0 a r q1
q0 1 b r q1
q0 * * r reject
q0 a a l q4
q0 b b l q7

;State q1:read the 0's or 1's
q1 0 0 r q1
q1 1 1 r q1
q1 _ _ l q2
q1 a 0 l q2
q1 b 1 l q2
q1 * * l reject

;State q2
q2 0 a l q3
q2 1 b l q3
q2 * * l reject

;State q3
q3 0 0 l q3
q3 1 1 l q3
q3 a 0 r q0
q3 b 1 r q0
q3 * * r reject

;State q4
q4 _ _ r q5
q4 0 0 l q4
q4 1 1 l q4
q4 z z r q5
q3 * * l reject

;State q5
q5 0 z r q6
q5 * * l reject

;State q6
q6 0 0 r q6
q6 1 1 r q6
q6 a 0 r q10
q6 * * l reject

;State q7
q7 0 0 l q7
q7 1 1 l q7
q7 _ _ r q8
q7 z z r q8
q7 * * l reject

;State q8
q8 1 z r q9
q8 * * l reject

;State q9
q9 0 0 r q9
q9 1 1 r q9
q9 b 1 r q10
q8 * * l reject

;State q10
q10 _ _ l accept
q10 1 b l q7
q10 0 a l q4
q10 * * l reject

;State reject
reject * * r reject
reject _ _ l reject0
reject0 * _ l reject0
reject0 _ F r reject2
reject2 _ a r reject3
reject3 _ l r reject4
reject4 _ s r reject5
reject5 _ e * halt_reject

accept * * r accept
accept _ _ l accept0
accept0 * _ l accept0
accept0 _ T r accept2
accept2 _ r r accept3
accept3 _ u r accept4
accept4 _ e * halt_accept



