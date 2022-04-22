module com.example.es2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;
//
//    requires org.controlsfx.controls;
//    requires com.dlsc.formsfx;
//    requires validatorfx;
//    requires org.kordamp.bootstrapfx.core;
//    requires eu.hansolo.tilesfx;



    opens com.example.es2 to javafx.fxml;
    requires jssc;
    exports com.example.es2;
}