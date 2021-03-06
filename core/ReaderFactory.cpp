//---------------------------------------------------------------------------



#include "ReaderFactory.h"
#include "WriterFactory.h"
#include "RtfReader.h"
#include "HtmlReader.h"
#include "TextReader.h"

//---------------------------------------------------------------------------



namespace DoxEngine
{
  template <class T> class ReaderFactoryTemplate: public ReaderFactory
  {
    virtual ReadInterface* Create(std::istream &stream, WriterInterface &writer, DebugLog& newLog)
    {
      return new T(stream, writer, newLog);
    }
  };

  ReaderFactories& ReaderFactoriesSingleton::GetReaderFactories()
  {
    // This function should only be called from the main thread
    static ReaderFactories* readers = NULL;

    if (!readers)
    {
      readers = new ReaderFactories;
      readers->insert(ReaderFactories::value_type(FORMAT_RTF, ReaderFactoryPtr(new ReaderFactoryTemplate<RtfReader>)));
      readers->insert(ReaderFactories::value_type(FORMAT_HTML, ReaderFactoryPtr(new ReaderFactoryTemplate<HtmlReader>)));
      readers->insert(ReaderFactories::value_type(FORMAT_TEXT, ReaderFactoryPtr(new ReaderFactoryTemplate<TextReader>)));
    }

    return *readers;

  }

}
