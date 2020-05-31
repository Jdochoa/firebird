********************************************************************************
  LIST OF KNOWN INCOMPATIBILITIES
  between versions 3.0 and 4.0
********************************************************************************

This document describes all the changes that make v4.0 incompatible in any way
as compared with the previous releases and hence could affect your databases and
applications.

Please read the below descriptions carefully before upgrading your software to
the new Firebird version.

Deprecating UDF
--------------------------
  * Initial design of UDF always used to be security problem. The most dangerous
	security holes when UDFs and external tables are used simultaneousky were
	fixed in FB 1.5. But even after it incorrectly declared (using SQL statement
	DECLARE EXTERNAL FUNCTION) UDF can easily cause various security issues like
	server crash or execution of arbitrary code. Therefore UDFs are deprecated
	in v4. That means that UDFs can't be used with default configuration
	(parameter "UdfAccess" set to "None") and all sample UDF libraries (ib_udf,
	fbudf) are not distributed any more. Most of functions in that libraries
	were replaced with builtin analogs in previous versions and therefore
	already deprecated. A few remaining functions got safe replacement in UDR
	library "udf_compat", namely div, frac, dow, sdow, getExactTimestampUTC and
	isLeapYear. Users who still wish to use UDFs should set "UdfAccess" to
	"Restrict <path-list>". If you never used to modify this parameter before
	path-list is just UDF and resulting line in firebird.conf should be:
	UdfAccess = Restrict UDF
	Recommended long-term solution is replacing of UDF with UDR.


Non-constant date/time/timestamp literals
-----------------------------------------
  * There is date, time and timestamp literals with this syntax:
	DATE '2018-01-01'
	TIME '10:00:00'
	TIMESTAMP '2018-01-01 10:00:00'

	They are parsed at compile time.

	However, there are weird situation with some literals.

	We may use things as DATE 'TODAY', DATE 'TOMORROW', DATE 'YESTERDAY', TIME 'NOW' and TIMESTAMP 'NOW'.

	And different than these strings used in CAST, these are literais
	(evaluated at compile time).

	So if you create a procedure/function with them, they value are
	refreshed every time you recompile (from SQL) the routine, but never
	refreshed when you run it.

	Also imagine a compiled statement cache (implementation detail), a
	"select timestamp 'now' from rdb$database" will give stalled results.

	These strings will not be accepted with the literals syntax anymore.
