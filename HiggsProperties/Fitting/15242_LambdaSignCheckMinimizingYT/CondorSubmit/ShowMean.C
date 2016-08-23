{
    ResultTree->Draw("P1", "P1Error > 0 && P3Error == 0 && P6Error == 0");
    cout << "A2ZZ " << htemp->GetMean() << " +- " << htemp->GetMeanError() << endl;
    ResultTree->Draw("P2", "P1Error > 0 && P3Error == 0 && P6Error == 0");
    cout << "A3ZZ " << htemp->GetMean() << " +- " << htemp->GetMeanError() << endl;
    ResultTree->Draw("P4", "P1Error > 0 && P3Error == 0 && P6Error == 0");
    cout << "A2ZA " << htemp->GetMean() << " +- " << htemp->GetMeanError() << endl;
    ResultTree->Draw("P5", "P1Error > 0 && P3Error == 0 && P6Error == 0");
    cout << "A3ZA " << htemp->GetMean() << " +- " << htemp->GetMeanError() << endl;
    ResultTree->Draw("P7", "P1Error > 0 && P3Error == 0 && P6Error == 0");
    cout << "A2AA " << htemp->GetMean() << " +- " << htemp->GetMeanError() << endl;
    ResultTree->Draw("P8", "P1Error > 0 && P3Error == 0 && P6Error == 0");
    cout << "A3AA " << htemp->GetMean() << " +- " << htemp->GetMeanError() << endl;
}
