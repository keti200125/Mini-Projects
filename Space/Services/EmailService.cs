using System.Net;
using System.Net.Mail;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space.Services
{
    public class EmailService
    {
        public void SendReport(string senderEmail, string password, 
            string receiverEmail, string filePath= "shortest_path.csv")
        {
            try
            {
                MailMessage message = new MailMessage(senderEmail, receiverEmail);
                message.Subject = "Cosmic Navigation Report";
                message.Attachments.Add(new Attachment(filePath));

                SmtpClient smtp = new SmtpClient("smtp.gmail.com", 587);
                smtp.Credentials = new NetworkCredential(senderEmail, password);
                smtp.EnableSsl = true;

                smtp.Send(message);
                Console.WriteLine("Report is sent.");
            }
            catch (Exception ex)
            {
                Console.WriteLine("Report error: " + ex.Message);
            }
        }
    }
}

