//
//  WeatherGetter.swift
//  Saving Life Final
//
//  Created by Kanyanee P on 20/4/2562 BE.
//  Copyright © 2562 Kanyanee P. All rights reserved.
//

import Foundation
import SwiftyJSON
protocol WeatherGetterDelegate {
    func didGetWeather(weather: Weather)
    func didNotGetWeather(error: NSError)
}

class WeatherGetter {
    //private let openWeatherMapBaseURL = "http://api.openweathermap.org/data/2.5/forecast?id=7026800&APPID=e3a767d8163b6b127dd934461d3f442a"
    private let openWeatherMapAPIKey = "e3a767d8163b6b127dd934461d3f442a"
    private let openWeatherMapBaseURL = "http://api.openweathermap.org/data/2.5/weather"
    private var delegate: WeatherGetterDelegate
    
    
    // MARK: -
    
    init(delegate: WeatherGetterDelegate) {
        self.delegate = delegate
    }
    
    var weatherInformation: Weather?
    func getWeather() {
        let session = URLSession.shared
        //let weatherRequestURL = NSURL(string: "\(openWeatherMapBaseURL)?APPID=\(openWeatherMapAPIKey)&q=Tampa")!
        let weatherRequestURL = NSURL(string:
            "http://api.openweathermap.org/data/2.5/forecast?id=7026800&APPID=e3a767d8163b6b127dd934461d3f442a")!
        let dataTask = session.dataTask(with: weatherRequestURL as URL, completionHandler: {
            (data, response, error) in
            if let error = error {
                // Case 1: Error
                // We got some kind of error while trying to get data from the server.
                print("Error:\n\(error)")
            }
            else{
                do {
                    // Try to convert that data into a Swift dictionary
                    //let weatherRaw = try JSONSerialization.jsonObject(with: data!,options: .mutableContainers) as! [String: AnyObject]
                    let weatherRaw  = try JSONSerialization.jsonObject(with: data!,options: .mutableContainers) as! Dictionary< String, Any>
                    //print(weatherData)
    
                    
                    let weatherJSON = JSON(weatherRaw)
                    //print(weatherJSON)
                    let weatherData = try JSONDecoder().decode(Weather.self, from: weatherJSON.rawData())
                    self.weatherInformation = weatherData
                }
                catch let jsonError as NSError {
                    // An error occurred while trying to convert the data into a Swift dictionary.
                    self.delegate.didNotGetWeather(error: jsonError)
                }
            }
        })
        dataTask.resume()
    }
    
}
