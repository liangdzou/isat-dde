function Aco = Aco_cal(a0, a1, xi, xi1, TEMP, Ivar)

Fdec = subs(subs(TEMP,xi,xi1),a0,a1)-TEMP;
Fa1 = eval(['@(', strrep(strrep(Mat2Str([a0(:);xi;xi1]),'[',''),']',''), ') [', Mat2Str(Fdec), ']']);

Sa1 = 'Fa1(';
for j = 1 : size(Ivar,2)-1
    Sa1 = strcat(Sa1, 'Ivar(', num2str(j), '), ');
end
Sa1 = strcat(Sa1, 'Ivar(', num2str(size(Ivar,2)), '))');
Aco = eval(Sa1);

end

function elementsStr = Mat2Str(Mat)

Mat = transpose(Mat(:));
MatStr = vectorize(Mat);
i = strfind(MatStr, '[[');
j = strfind(MatStr, '])');
elementsStr = MatStr(i+1 : j-1);

end

% backup
% function Ia1 = getIa1(a0, a1, d0, Ia0, Ixi)
% 
% Fa1 = eval(['@(', strrep(strrep(Mat2Str([a0,d0]),'[',''),']',''), ') [', Mat2Str(a1), ']']);
% Sa1 = 'Fa1(';
% for i = 1 : size(a0,1)
%     for j = 1 : size(a0,2)
%         Sa1 = strcat(Sa1, 'Ia0(', num2str(i), ',', num2str(j), '), ');
%     end
% end
% for i = 1 : (size(a0,1)-1)
%     Sa1 = strcat(Sa1, 'Ixi(', num2str(i), '), ');
% end
% Sa1 = strcat(Sa1, 'Ixi(', num2str(size(a0,1)), '))');
% Ia1 = eval(Sa1);
% 
% end
