										/* operators */
<xx>\\=				TC(EQ)				/* some = value */
<xx>\\[				TC(LQ)				/* [list begin */
<xx>\\]				TC(RQ)				/* list end]   */
<xx>\\(				TC(LP)				/* (grouping begin */
<xx>\\)				TC(RP)				/*  grouping end) */
<xx>\\<				TC(LL)				/* <vector begin */
<xx>\\>				TC(GG)				/*  vector end>  */
<xx>\\:				TC(COLON)			/* some:pair */
#<xx>\\+				TC(ADD)
#<xx>\\-				TC(SUB)
#<xx>\\*				TC(MUL)
#<xx>\\/				TC(DIV)
#<xx>\\^				TC(POW)
