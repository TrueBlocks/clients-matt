/*-----------------------------------------------------------------------
 * qblocks - fast, fully-decentralized data from blockchains
 *----------------------------------------------------------------------*/
#include "acctlib.h"

//-----------------------------------------------------------------------
class CMattTraverser : public CTraverser {
    // In this example, we do not use this derived class from the
    // CTraverser class. We could use this class to accumulate custom
    // data during the traversal such as summaries, totals, averages, etc.
  public:
    CMattTraverser(void) : CTraverser(cout, "matt") {
    }
};

//-----------------------------------------------------------------------
// Proir to visiting any transactions for the given address, TrueBlocks
// calls into the traverser's `preFunc`. Here's we've called that routine
// `init`, and we use the function to display the field list in the header
// of the generated data.
bool init(CTraverser* trav, void* data) {
    cout << "block\t";
    cout << "txid\t";
    cout << "date\t";
    cout << "address\t";
    cout << "exchangeRateStored" << endl;
    return true;
}

//-----------------------------------------------------------------------
// A traverser's `displayFunc` gets called once for each transaction in
// that the given address has appeared in. Here, we display some basic
// information about the transaction (blockNumber, etc.) and then we call
// into the smart contract with the four-byte code (0x182df0f5) for the
// function we're interested in. This function is called exchangeRateStored.
bool visit(CTraverser* trav, void* data) {
    const address_t compoundAddr = "0x5d3a536E4D6DbD6114cc1Ead35777bAB948E3643";
    CEthCall theCall;
    theCall.address = compoundAddr;
    theCall.encoding = "0x182df0f5";
    theCall.bytes = "";
    theCall.blockNumber = trav->trans.blockNumber;
    theCall.abi_spec.loadAbiFromEtherscan(compoundAddr);
    doEthCall(theCall);

    cout << trav->trans.blockNumber << "\t";
    cout << trav->trans.transactionIndex << "\t";
    cout << trav->trans.Format("[{DATE}]") << "\t";
    cout << theCall.getResults() << endl;

    return true;
}

//-----------------------------------------------------------------------
extern "C" CTraverser* makeTraverser(void) {
    // Each custom traverser needs to produce a `makeTraverser` routine.
    freshenTimestamps(getBlockProgress().client);
    loadTimestamps(&expContext().tsMemMap, expContext().tsCnt);

    // Create the class...
    CMattTraverser* trav = new CMattTraverser;

    // Assign it's functions
    trav->filterFunc = trav->postFunc = trav->dataFunc = noopFunc;
    trav->preFunc = init;
    trav->displayFunc = visit;

    // return it to caller (caller must clean up memory)
    return trav;
}
