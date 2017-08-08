% This function finds the time derivative of a symbolic expression.  
% Symbolic Math Toolbox is required.  Based on Lagrange.m.
% 
% time_derivative=ddt(expression,V)
%
% expression = Symbolic expression we want time derivative of.
% V   = System Variables (symbolic) [q1 dq1 ddq1 q2 dq2 ddq2... qn dqn
% ddqn].
% time_deriviative = Time derivative of the expression.

function time_derivative=ddt(expr,V)
syms t;
Var=length(V)/3;
Vt=V;
    for cont0=1:1:Var
        Vt(cont0*3-2)=strcat('f',num2str(cont0),'(t)');
        Vt(cont0*3-1)=diff(Vt((cont0*3)-2),t);
        Vt(cont0*3)=diff(Vt((cont0*3)-2),t,2);
    end

    Dposx=expr;

    for cont=1:1:Var*3         
         Dposx=subs(Dposx,V(cont),Vt(cont));
    end
    L1=diff(Dposx,t);

    for cont=Var*3:-1:1         %
         L1=subs(L1,Vt(cont),V(cont));
    end
        L1F=simplify(expand(L1));
        L1F=collect(L1F,Vt(cont0*3));%*****************
        time_derivative=L1F;