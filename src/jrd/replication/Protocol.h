/*
 *  The contents of this file are subject to the Initial
 *  Developer's Public License Version 1.0 (the "License");
 *  you may not use this file except in compliance with the
 *  License. You may obtain a copy of the License at
 *  http://www.ibphoenix.com/main.nfs?a=ibphoenix&page=ibp_idpl.
 *
 *  Software distributed under the License is distributed AS IS,
 *  WITHOUT WARRANTY OF ANY KIND, either express or implied.
 *  See the License for the specific language governing rights
 *  and limitations under the License.
 *
 *  The Original Code was created by Dmitry Yemanov
 *  for the Firebird Open Source RDBMS project.
 *
 *  Copyright (c) 2013 Dmitry Yemanov <dimitr@firebirdsql.org>
 *  and all contributors signed below.
 *
 *  All Rights Reserved.
 *  Contributor(s): ______________________________________.
 */


#ifndef JRD_REPLICATION_PROTOCOL_H
#define JRD_REPLICATION_PROTOCOL_H

namespace Replication
{
	inline ULONG ENCODE_PROTOCOL(ULONG major, USHORT minor)
	{
		return ((major << 8) | minor);
	}

	// Supported protocol versions
	const ULONG PROTOCOL_VERSION_1 = 1;
	const ULONG PROTOCOL_1_0 = ENCODE_PROTOCOL(PROTOCOL_VERSION_1, 0);
	const ULONG PROTOCOL_CURRENT_VERSION = PROTOCOL_1_0;

	struct Block
	{
		FB_UINT64 traNumber;
		ULONG protocol;
		ULONG dataLength;
		ULONG metaLength;
		ULONG flags;
		ISC_TIMESTAMP timestamp;
	};

	const ULONG BLOCK_BEGIN_TRANS = 1;
	const ULONG BLOCK_END_TRANS = 2;

	enum Operation
	{
		opStartTransaction = 1,
		opPrepareTransaction = 2,
		opCommitTransaction = 3,
		opRollbackTransaction = 4,
		opCleanupTransaction = 5,

		opStartSavepoint = 6,
		opReleaseSavepoint = 7,
		opRollbackSavepoint = 8,

		opInsertRecord = 9,
		opUpdateRecord =  10,
		opDeleteRecord = 11,
		opStoreBlob = 12,
		opExecuteSql = 13,
		opSetSequence = 14,
		opExecuteSqlIntl = 15
	};

} // namespace

#endif // JRD_REPLICATION_PROTOCOL_H

