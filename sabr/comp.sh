./bw/bw \
 -hmmdir cmu-en-us \
 -moddeffn cmu-en-us/mdef \
 -ts2cbfn .cont. \
 -feat 1s_c_d_dd \
 -cmn current \
 -agc none \
 -lda cmu-en-us/feature_transform \
 -dictfn cmudict-en-us.dict \
 -ctlfn sabr.fileids \
 -lsnfn sabr.transcription \
 -accumdir .

 ./mllr_solve/mllr_solve \
    -meanfn cmu-en-us/means \
    -varfn cmu-en-us/variances \
    -outmllrfn mllr_matrix -accumdir .

cp -a cmu-en-us en-us-adapt

./map_adapt/map_adapt \
    -moddeffn cmu-en-us/mdef \
    -ts2cbfn .ptm. \
    -meanfn cmu-en-us/means \
    -varfn cmu-en-us/variances \
    -mixwfn cmu-en-us/mixture_weights \
    -tmatfn cmu-en-us/transition_matrices \
    -accumdir . \
    -mapmeanfn en-us-adapt/means \
    -mapvarfn en-us-adapt/variances \
    -mapmixwfn en-us-adapt/mixture_weights \
    -maptmatfn en-us-adapt/transition_matrices
