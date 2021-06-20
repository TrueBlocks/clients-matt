/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2016, 2021 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *------------------------------------------------------------------------*/
#include "acctlib.h"
#include "pricepershare.h"

map<address_t, bool> headerMap;
map<address_t, blknum_t> lastBlockMap;
//-----------------------------------------------------------------------
class CMattTraverser : public CTraverser {
public:
    bool reported = false;
    CMattTraverser(void) : CTraverser(cout, "matt") {
        CMonitor::registerClass();
    }
};

//------------------------------------------------------------------------------------------------
bool init(CTraverser* trav, void* data) {
    CMattTraverser *mt = (CMattTraverser*)trav;
    if (!mt->reported) {
        for (auto item : trav->monitorMap) {
            CMonitor monitor = item.second;
            string_q res = monitor.Format("Reporting on [{ADDRESS}]\t[{NAME}]");
            cerr << res << endl;
        }
        mt->reported = true;
    }
    return true;
}

//------------------------------------------------------------------------------------------------
bool visit(CTraverser* trav, void* data) {
    CMattTraverser *mt = (CMattTraverser*)trav;
    CPricePerShare share = mt->trans;
    share.address = mt->curMonitor->address;

    if (!headerMap[mt->curMonitor->address]) {
        headerMap[mt->curMonitor->address] = true;

        CPricePerShare share;
        cout << toLower(share.Format(substitute(substitute(STR_DISPLAY_PRICEPERSHARE, "{", "{p:"), "\t", ","))) << endl;

        string_q fileName = "./" + mt->curMonitor->address + ".txt";
        if (fileExists(fileName)) {
            string_q orig = asciiFileToString(fileName);
            string_q content = orig;
            CStringArray lines;
            explode(lines, content, '\n');
            string_q lastLine = lines[lines.size() - 1];
            cout << lastLine << endl;
            lastLine = lastLine.substr(lastLine.find(",")+1);
            cout << lastLine << endl;
            lastLine = lastLine.substr(lastLine.find("\"")+1);
            cout << lastLine << endl;
            lastBlockMap[mt->curMonitor->address] = str_2_Uint(lastLine);
            cout << orig;
        }
    }

    if (mt->trans.blockNumber <= lastBlockMap[mt->curMonitor->address]) {
        cerr << mt->trans.blockNumber << "." << mt->trans.transactionIndex << "    \r";
        cerr.flush();
        // getchar();
        return true;
    }

    string_q res = share.Format(STR_DISPLAY_PRICEPERSHARE);
    cerr << res << endl;

    // CEthCall theCall;
    // theCall.address = trav->curMonitor->address;
    // theCall.encoding = "0x99530b06";
    // theCall.bytes = "";
    // theCall.blockNumber = trav->trans.blockNumber;
    // theCall.abi_spec.loadAbiFromEtherscan(trav->curMonitor->address);
    // doEthCall(theCall);

    // ostringstream os;
    // os << "\"" << colorMap[trav->curMonitor->address] << trav->curMonitor->address << cOff << "\",";
    // os << "\"" << trav->trans.blockNumber << "\",";
    // os << "\"" << trav->trans.transactionIndex << "\",";
    // os << "\"" << trav->trans.Format("[{DATE}]") << "\",";
    // os << "\"" << str_2_Wei(theCall.getResults()) << "\"";
    // os << endl;
    // appendToAsciiFile("./" + trav->curMonitor->address + ".txt", os.str());
    // cout << os.str();

    return true;
}

//-----------------------------------------------------------------------
extern "C" CTraverser* makeTraverser(void) {
    freshenTimestamps(getBlockProgress().client);
    loadTimestamps(&expContext().tsMemMap, expContext().tsCnt);
    CMattTraverser* trav = new CMattTraverser;
    trav->filterFunc = trav->postFunc = trav->dataFunc = noopFunc;
    trav->preFunc = init;
    trav->displayFunc = visit;
    return trav;
}
