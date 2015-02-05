a_w = 1000;
nums = 100;
numxi = 1;

xi1 = sym('xia',size(xi));
ly1 = subs(subs(ly, a0, a1), xi, xi1);
decrease = ly - ly1;

% first nums steps, suppose xi is always Delta/2
ly_vals = zeros(1, nums);
vala = [INIT,zeros(size(a0,1),size(a0,2)-1)];
valxi = DELTA*ones(size(xi));
for i = 1 : nums
    ly_vals(i) = eval(subs(subs(subs(ly, a0, vala), xi, valxi), xi1, valxi));
    vala = eval(subs(subs(subs(a1,a0,vala),xi,valxi),xi1,valxi));
end

de_vals = zeros(1, nums);
for i = 1 : nums-1
    de_vals(i) = ly_vals(i) - ly_vals(i+1);
end

% % random check
% valxi = 0;
% vala = -a_w;
% for i = 1 : 2 * nums
%     vala = vala + a_w/nums;
%     eval(subs(subs(subs(decrease, a0, vala*ones(size(a0))), xi, valxi*ones(size(xi))), xi1, valxi*ones(size(xi))))
% end
