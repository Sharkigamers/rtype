#include "Types.hpp"

Signature flagTosignature(systemSignature sig)
{
    Signature res;
    std::string binary = Signature(sig).to_string();
    for (size_t i = 0; i <= binary.size(); ++i)
    {
        if (binary[i] == '1') {
            res.set(31 - i);
        }
    }
    return (res);
};

bool checkSignature(Signature entSig, Signature sysSig)
{
    std::string entSigStr = Signature(entSig).to_string();
    std::string sysSigStr = Signature(sysSig).to_string();

    for (size_t i = 0; i <= sysSigStr.size(); ++i) {
        if (sysSigStr[i] == '1' && entSigStr[i] != '1')
            return (false);
    }
    return (true);

}

bool checkIfComponent(const Signature &entSig, const componentSignature &compSig)
{
    auto entSigStr = Signature(entSig).to_string();
    if (entSigStr[31 - compSig] == '1')
        return (true);
    return false;
}