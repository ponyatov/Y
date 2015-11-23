\\\$					{BEGIN(xx);TC(SX);}	/* expression mode on: inline str*/
\\\?					{BEGIN(xx);TC(QX);}	/* expression mode on: debug dump */
<xx>[\\\$\\\?]			{BEGIN(INITIAL);}	/* expression mode off (inline) */
<xx>[ \\t\\r\\n]+		{}					/* drop spaces in expression mode */
