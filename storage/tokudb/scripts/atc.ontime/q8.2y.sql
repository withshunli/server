SELECT DestCityName, COUNT( DISTINCT OriginCityName) FROM ontime WHERE Year BETWEEN 1999 and 2000 GROUP BY DestCityName ORDER BY 2 DESC LIMIT 10;
