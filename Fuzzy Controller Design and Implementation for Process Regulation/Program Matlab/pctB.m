fis = readfis("fuzzyMamdani_pct1_proj.fis");

u=zeros(5,11);
i=1;
for e = -1.0:0.2:1.0
    j=1;
    for de = -1.0:0.5:1.0 
        inputs = [e de];                   
        u(j,i) = evalfis(fis,inputs);         
        j=j+1;
    end
    i=i+1;
end
u