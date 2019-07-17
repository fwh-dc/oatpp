/***************************************************************************
 *
 * Project         _____    __   ____   _      _
 *                (  _  )  /__\ (_  _)_| |_  _| |_
 *                 )(_)(  /(__)\  )( (_   _)(_   _)
 *                (_____)(__)(__)(__)  |_|    |_|
 *
 *
 * Copyright 2018-present, Leonid Stryzhevskyi <lganzzzo@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ***************************************************************************/

#ifndef oatpp_web_mime_multipart_Part_hpp
#define oatpp_web_mime_multipart_Part_hpp

#include "oatpp/core/data/share/MemoryLabel.hpp"
#include "oatpp/core/data/stream/Stream.hpp"

#include <unordered_map>

namespace oatpp { namespace web { namespace mime { namespace multipart {

/**
 * One part of the multipart.
 */
class Part {
public:
  /**
   * Typedef for headers map. Headers map key is case-insensitive.
   * `std::unordered_map` of &id:oatpp::data::share::StringKeyLabelCI_FAST; and &id:oatpp::data::share::StringKeyLabel;.
   */
  typedef std::unordered_map<oatpp::data::share::StringKeyLabelCI_FAST, oatpp::data::share::StringKeyLabel> Headers;
private:
  oatpp::String m_name;
  oatpp::String m_filename;
  Headers m_headers;
  std::shared_ptr<data::stream::InputStream> m_inputStream;
  oatpp::String m_inMemoryData;
  data::v_io_size m_knownSize;
public:

  /**
   * Constructor.
   * @param headers - headers of the part.
   * @param inputStream - input stream of the part data.
   * @param inMemoryData - possible in-memory data of the part. Same data as the referred by input stream. For convenience purposes.
   * @param knownSize - known size of the data in the input stream. Pass `-1` value if size is unknown.
   */
  Part(const Headers& headers,
       const std::shared_ptr<data::stream::InputStream>& inputStream,
       const oatpp::String inMemoryData,
       data::v_io_size knownSize);

  /**
   * Constructor.
   * @param headers - headers of the part.
   */
  Part(const Headers& headers);

  /**
   * Set part data info.
   * @param inputStream - input stream of the part data.
   * @param inMemoryData - possible in-memory data of the part. Same data as the referred by input stream. For convenience purposes.
   * @param knownSize - known size of the data in the input stream. Pass `-1` value if size is unknown.
   */
  void setDataInfo(const std::shared_ptr<data::stream::InputStream>& inputStream,
                   const oatpp::String inMemoryData,
                   data::v_io_size knownSize);

  /**
   * Get name of the part.
   * @return - name of the part.
   */
  oatpp::String getName() const;

  /**
   * Get filename of the part (if applicable).
   * @return - filename.
   */
  oatpp::String getFilename() const;

  /**
   * Get request's headers map.
   * @return Headers map
   */
  const Headers& getHeaders() const;

  /**
   * Get header value
   * @param headerName
   * @return header value
   */
  oatpp::String getHeader(const oatpp::data::share::StringKeyLabelCI_FAST& headerName) const;

  /**
   * Get input stream of the part data.
   * @return - input stream of the part data.
   */
  std::shared_ptr<data::stream::InputStream> getInputStream() const;

  /**
   * Get in-memory data (if applicable). <br>
   * It may be possible set for the part in case of storing part data in memory. <br>
   * This property is optional. Preferred way to access data of the part is through `getInputStream()` method.
   * @return - in-memory data.
   */
  oatpp::String getInMemoryData() const;

  /**
   * Return known size of the part data.
   * @return - known size of the part data. `-1` - if size is unknown.
   */
  data::v_io_size getKnownSize() const;

};

}}}}

#endif // oatpp_web_mime_multipart_Part_hpp
