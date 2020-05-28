#ifndef IDX_FILE
#define IDX_FILE

#include <cstdint>
#include <fstream>
#include <string>
#include <map>

namespace ml
{

  enum class idxDataType : char {
    kUnsignedByte = 0x08,
    kSignedByte = 0x09,
    kShort = 0x0B,
    kInt = 0x0C,
    kFloat = 0x0D,
    kDouble = 0x0E
  };

  const std::map<idxDataType, uint8_t> idxDataByteSizes = {
    { idxDataType::kUnsignedByte, 1 },
    { idxDataType::kSignedByte, 1 },
    { idxDataType::kShort, 2 },
    { idxDataType::kInt, 4 },
    { idxDataType::kFloat, 4 },
    { idxDataType::kDouble, 8 }
  };

  class idx_file
  {

  private:

    uint32_t* _dimensionSizes = nullptr;
    void* _data = nullptr;

    uint32_t _dataBytes = 1;
    uint8_t _dimensions = 0;
    idxDataType _dataType = idxDataType::kUnsignedByte;

    void ReadMagicNumber( std::ifstream& stream );
    uint16_t swapByteOrder( uint16_t data );
    uint32_t swapByteOrder( uint32_t data );
    uint64_t swapByteOrder( uint64_t data );

  public:

    idx_file() = default;
    idx_file( const std::string& fileName );
    virtual ~idx_file();

    bool load( const std::string& fileName );
    bool print( const std::string& fileName );
    void print( std::ostream& stream );
    void* data();
    idxDataType type();
    uint8_t dimensions();
    uint32_t dimensionSize( int dimension );
  };

}
#endif