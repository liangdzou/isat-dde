function matAverage = getMatAverage(mats,xi)

n = size(xi,1);
matAverage = xi(1)*mats(:,:,1);
for i = 2 : n
    matAverage = matAverage + xi(i,1)*mats(:,:,i);
end

end