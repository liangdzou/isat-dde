function subVector = getSubVector(vector,m,n)

subVector = zeros(n-m+1,1);
for i = m : n
    subVector(i-m+1) = vector(i);
end

end