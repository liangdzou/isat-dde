function elementsStr = vectElementsString(vect)

vectStr = vectorize(vect);
i = strfind(vectStr, '[[');
j = strfind(vectStr, '])');
elementsStr = vectStr(i+1 : j-1);

end