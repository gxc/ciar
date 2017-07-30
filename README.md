# ciar

  ciar - COUNTRY IP ADDRESS RANGES
  
  Extract IP address ranges of a country from the IP2Location IPV4 CSV data

  Version 0.1

  Tip: The output could be used as the Shadowsocks ACL whitelist/blacklist

  [IP2Location LITE IP-COUNTRY Database](http://lite.ip2location.com/database/ip-country)

### How to use? ###

  Download the newest IP2Location IPV4 CSV data

  Get IP address rangs of a country by executing ciar:

```
  ciar csv_file country_code [output_file]

  If an output file is not specified, the standard output is used.
```

  Example:
  ```
  ./ciar IP2LOCATION-LITE-DB1.CSV CN ss_whitelist.acl
  ```

### License ###
[Licensed under the Apache License, Version 2.0.](http://www.apache.org/licenses/LICENSE-2.0)
