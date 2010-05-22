#include <string>

/**
 * Replace all occurrences of string orgSubstr in string target with the new
 * string newSubstr. For example, replacing "!=" with " not_eq " in "i!=2"
 * will return "i not_eq 2 "
 */

void replaceAll( 
    const char * orgSubstr, 
    const char * newSubstr, 
    std::string & target )
{
  size_t pos = 0;
  size_t newStrlen = strlen( newSubstr );
  size_t orgStrlen = strlen( orgSubstr );
  /* loop through the string finding each occurrence of orgSubstr until the
   * search leaves the end of the string (std::string::npos).
   */
  while( 
      ( pos = target.find( orgSubstr, pos ) ) != std::string::npos )
  {
    target.replace( pos, orgStrlen, newSubstr );
  }
}

