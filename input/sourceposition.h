#ifndef __FILTERGEN_INPUT_SOURCEPOSITION_H__
#define __FILTERGEN_INPUT_SOURCEPOSITION_H__

#include <iostream>

class SourcePosition
{
public:
  /** Constructor.
   * @param filename the name of the file that the source position is in
   * @param linestart the line number that the source position starts on
   * @param colstart the column number that the source position starts on
   * @param lineend the line number that the source position ends on
   * @param colend the column number that the source positoin ends on
   */
  SourcePosition(std::string filename,
		 int linestart = 0, int colstart = 0,
		 int lineend = 0, int colend = 0);
  SourcePosition(int linestart = 0, int colstart = 0,
		 int lineend = 0, int colend = 0);

  /** Output stream operator.
   * Renders the source position to the output stream in the GNU
   * coding standards style.
   * http://www.gnu.org/prep/standards/html_node/Errors.html#Errors
   * @param os the output stream
   * @param sourceposition the SourcePosition object being streamed
   */
  friend std::ostream & operator<<(std::ostream & os,
				   const SourcePosition & sourceposition);

private:
  const std::string filename;
  const int linestart;
  const int colstart;
  const int lineend;
  const int colend;

  friend class SourcePositionTest;
};

#endif // __FILTERGEN_INPUT_SOURCEPOSITION_H__