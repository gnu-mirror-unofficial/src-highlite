#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <iostream>

#include "asserttestexit.h"
#include "srchilite/wordtokenizer.h"
#include "srchilite/tostringcollection.h"

using namespace std;
using namespace srchilite;

/*
 * We have to use 'std' namespaces because 'WordTokenizer::WordTokenizerResults::value_type'
 * is an std::pair<std::string, std::string> in disguise. We have to place 'operator<<()'
 * into the same namespace for ADL to work. Otherwise gcc-12 or clang-13 can't find the
 * overload.
 */
namespace std {

static ostream &operator <<(ostream &os, const WordTokenizer::WordTokenizerResults::value_type &);

ostream &operator <<(ostream &os, const WordTokenizer::WordTokenizerResults::value_type &token) {
    if (token.first.size()) {
        os << "space: \"" << token.first << "\"" << endl;
    } else {
        os << "word : \"" << token.second << "\"" << endl;
    }

    return os;
}

}

int main() {
    WordTokenizer::WordTokenizerResults tokens;

    WordTokenizer::tokenize(" Here  are\t \t some_words!", tokens);

    cout << "tokens: " << collectionToString(&tokens) << endl;

    WordTokenizer::WordTokenizerResults::const_iterator tok = tokens.begin();

    assertTrue(tok != tokens.end());
    assertEquals(" ", (tok++)->first);
    assertEquals("Here", (tok++)->second);
    assertEquals("  ", (tok++)->first);
    assertEquals("are", (tok++)->second);
    assertEquals("\t \t ", (tok++)->first);
    assertEquals("some_words!", (tok++)->second);

    cout << "test_wordtokenizer: SUCCESS" << endl;

    return 0;
}
