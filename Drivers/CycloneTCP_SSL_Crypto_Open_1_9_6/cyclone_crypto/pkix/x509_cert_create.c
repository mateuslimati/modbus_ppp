/**
 * @file x509_cert_create.c
 * @brief X.509 certificate generation
 *
 * @section License
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * Copyright (C) 2010-2019 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneCrypto Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.9.6
 **/

//Switch to the appropriate trace level
#define TRACE_LEVEL CRYPTO_TRACE_LEVEL

//Dependencies
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/core/crypto.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/pkix/x509_cert_create.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/pkix/x509_key_format.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/pkc/rsa.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/pkc/dsa.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/ecc/ecdsa.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/ecc/eddsa.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/ecc/ed25519.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/ecc/ed448.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/hash/sha1.h"
#include "../../../CycloneTCP_SSL_Crypto_Open_1_9_6/common/debug.h"

//Check crypto library configuration
#if (X509_SUPPORT == ENABLED)


/**
 * @brief Generate a X.509 certificate
 * @param[in] prngAlgo PRNG algorithm
 * @param[in] prngContext Pointer to the PRNG context
 * @param[in] certReqInfo Certificate request information
 * @param[in] subjectPublicKey Subject's public key (optional parameter)
 * @param[in] issuerCertInfo Issuer's certificate (optional parameter)
 * @param[in] serialNumber Serial number (optional parameter)
 * @param[in] validity Validity period
 * @param[in] signatureAlgo Signature algorithm
 * @param[in] signerPrivateKey Pointer to the issuer's private key
 * @param[out] output Buffer where to store the X.509 certificate
 * @param[out] written Length of the resulting X.509 certificate
 * @return Error code
 **/

error_t x509CreateCertificate(const PrngAlgo *prngAlgo, void *prngContext,
   const X509CertRequestInfo *certReqInfo, const void *subjectPublicKey,
   const X509CertificateInfo *issuerCertInfo, const X509SerialNumber *serialNumber,
   const X509Validity *validity, const X509SignatureAlgoId *signatureAlgo,
   const void *signerPrivateKey, uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   uint8_t *tbsCert;
   size_t tbsCertLen;
   const X509Name *issuer;
   const X509SubjectPublicKeyInfo *publicKeyInfo;
   X509AuthorityKeyId authKeyId;
   Asn1Tag tag;

   //Check parameters
   if(certReqInfo == NULL || validity == NULL || signatureAlgo == NULL ||
      signerPrivateKey == NULL || written == NULL)
   {
      return ERROR_INVALID_PARAMETER;
   }

   //Point to the buffer where to write the certificate
   p = output;
   //Length of the certificate
   length = 0;

   //Self-signed certificate?
   if(issuerCertInfo == NULL)
   {
      //Self-issued certificates are CA certificates in which the issuer
      //and subject are the same entity
      issuer = &certReqInfo->subject;

      //Where a CA distributes its public key in the form of a self-signed
      //certificate, the authority key identifier may be omitted
      authKeyId = certReqInfo->attributes.extensionReq.authKeyId;

      //Point to the subject's public key
      publicKeyInfo = &certReqInfo->subjectPublicKeyInfo;
   }
   else
   {
      //Check issuer's certificate version
      if(issuerCertInfo->tbsCert.version >= X509_VERSION_3)
      {
         const X509Extensions *extensions;

         //Point to the extensions of the issuer's certificate
         extensions = &issuerCertInfo->tbsCert.extensions;

         //Make sure the cA boolean is asserted
         if(!extensions->basicConstraints.cA)
            return ERROR_BAD_CERTIFICATE;

         //Check if the KeyUsage extension is present
         if(extensions->keyUsage.bitmap != 0)
         {
            //Make sure the keyCertSign is asserted
            if((extensions->keyUsage.bitmap & X509_KEY_USAGE_KEY_CERT_SIGN) == 0)
               return ERROR_BAD_CERTIFICATE;
         }
      }

      //The issuer field identifies the entity that has signed and issued
      //the certificate
      issuer = &issuerCertInfo->tbsCert.subject;

      //The KeyIdentifier field of the AuthorityKeyIdentifier extension must
      //be included in all certificates generated by conforming CAs to
      //facilitate certification path construction
      authKeyId.critical = FALSE;
      authKeyId.keyId = issuerCertInfo->tbsCert.extensions.subjectKeyId.value;
      authKeyId.keyIdLen = issuerCertInfo->tbsCert.extensions.subjectKeyId.length;

      //Point to the issuer's public key
      publicKeyInfo = &issuerCertInfo->tbsCert.subjectPublicKeyInfo;
   }

   //Format TBSCertificate structure
   error = x509FormatTbsCertificate(prngAlgo, prngContext, serialNumber,
      signatureAlgo, issuer, validity, &certReqInfo->subject,
      &certReqInfo->subjectPublicKeyInfo, subjectPublicKey,
      &certReqInfo->attributes.extensionReq, &authKeyId, p, &n);
   //Any error to report?
   if(error)
      return error;

   //The ASN.1 DER-encoded TBSCertificate is used as the input to the
   //signature function
   tbsCert = p;
   tbsCertLen = n;

   //Advance data pointer
   p += n;
   length += n;

   //Format SignatureAlgorithm structure
   error = x509FormatSignatureAlgo(signatureAlgo, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format SignatureValue structure
   error = x509FormatSignatureValue(prngAlgo, prngContext, tbsCert,
      tbsCertLen, signatureAlgo, publicKeyInfo, signerPrivateKey, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The certificate is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format TBSCertificate structure
 * @param[in] prngAlgo PRNG algorithm
 * @param[in] prngContext Pointer to the PRNG context
 * @param[in] serialNumber Serial number
 * @param[in] signatureAlgo Signature algorithm
 * @param[in] issuer Issuer's name
 * @param[in] validity Validity period
 * @param[in] subject Subject's name
 * @param[in] subjectPublicKeyInfo Subject's public key information
 * @param[in] publicKey Subject's public key
 * @param[in] extensions X.509 certificates extensions
 * @param[in] authKeyId AuthorityKeyIdentifier extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatTbsCertificate(const PrngAlgo *prngAlgo, void *prngContext,
   const X509SerialNumber *serialNumber, const X509SignatureAlgoId *signatureAlgo,
   const X509Name *issuer, const X509Validity *validity, const X509Name *subject,
   const X509SubjectPublicKeyInfo *subjectPublicKeyInfo, const void *publicKey,
   const X509Extensions *extensions, const X509AuthorityKeyId *authKeyId,
   uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;
   X509SubjectKeyId subjectKeyId;
   uint8_t digest[SHA1_DIGEST_SIZE];

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //Format Version field
   error = x509FormatVersion(X509_VERSION_3, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format SerialNumber field
   error = x509FormatSerialNumber(prngAlgo, prngContext, serialNumber, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format Signature field
   error = x509FormatSignatureAlgo(signatureAlgo, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format Issuer field
   error = x509FormatName(issuer, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format Validity field
   error = x509FormatValidity(validity, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format Subject field
   error = x509FormatName(subject, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format SubjectPublicKeyInfo field
   error = x509FormatSubjectPublicKeyInfo(subjectPublicKeyInfo, publicKey,
      digest, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The SubjectKeyIdentifier extension provides a means of identifying
   //certificates that contain a particular public key
   subjectKeyId.critical = FALSE;
   subjectKeyId.value = digest;
   subjectKeyId.length = SHA1_DIGEST_SIZE;

   //The Extensions field must only appear if the version is 3
   error = x509FormatExtensions(extensions, &subjectKeyId, authKeyId, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The TBSCertificate structure is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format Version field
 * @param[in] version Version number
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatVersion(X509Version version, uint8_t *output,
   size_t *written)
{
   error_t error;
   size_t n;
   Asn1Tag tag;

   //Encode the version number
   error = asn1WriteInt32(version, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Explicit tagging shall be used to encode version
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_CONTEXT_SPECIFIC;
   tag.objType = 0;
   tag.length = n;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format SerialNumber field
 * @param[in] prngAlgo PRNG algorithm
 * @param[in] prngContext Pointer to the PRNG context
 * @param[in] serialNumber Pointer to the serial number (optional parameter)
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatSerialNumber(const PrngAlgo *prngAlgo, void *prngContext,
   const X509SerialNumber *serialNumber, uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   Asn1Tag tag;

   //Valid serial number?
   if(serialNumber != NULL)
   {
      //The serial number is a unique integer assigned by the CA to each
      //certificate
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_INTEGER;
      tag.length = serialNumber->length;
      tag.value = serialNumber->data;
   }
   else
   {
      //Conforming CAs must not use serial number values longer than 20 octets
      error = prngAlgo->read(prngContext, output, X509_SERIAL_NUMBER_SIZE);
      //Any error to report?
      if(error)
         return error;

      //CAs must force the serial number to be a non-negative integer
      output[0] = (output[0] & 0x3F) | 0x40;

      //The serial number is a unique integer assigned by the CA to each
      //certificate
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_INTEGER;
      tag.length = X509_SERIAL_NUMBER_SIZE;
      tag.value = output;
   }

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format Name structure
 * @param[in] name Information about the name to be encoded
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatName(const X509Name *name, uint8_t *output,
   size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Initialize status code
   error = NO_ERROR;

   //Raw ASN.1 sequence?
   if(name->rawData != NULL && name->rawDataLen > 0)
   {
      //Copy raw ASN.1 sequence
      cryptoMemcpy(output, name->rawData, name->rawDataLen);
      //Total number of bytes that have been written
      *written = name->rawDataLen;
   }
   else
   {
      //Point to the buffer where to write the Name structure
      p = output;
      //Length of the Name structure
      length = 0;

      //Valid Country Name attribute?
      if(name->countryName != NULL && name->countryNameLen > 0)
      {
         //Encode Country Name attribute
         error = x509FormatNameAttribute(ASN1_TYPE_PRINTABLE_STRING,
            X509_COUNTRY_NAME_OID, sizeof(X509_COUNTRY_NAME_OID),
            name->countryName, name->countryNameLen, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Valid State Or Province Name attribute?
      if(name->stateOrProvinceName != NULL && name->stateOrProvinceNameLen > 0)
      {
         //Encode State Or Province Name attribute
         error = x509FormatNameAttribute(ASN1_TYPE_UTF8_STRING,
            X509_STATE_OR_PROVINCE_NAME_OID, sizeof(X509_STATE_OR_PROVINCE_NAME_OID),
            name->stateOrProvinceName, name->stateOrProvinceNameLen, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Valid Locality Name attribute?
      if(name->localityName != NULL && name->localityNameLen > 0)
      {
         //Encode Locality Name attribute
         error = x509FormatNameAttribute(ASN1_TYPE_UTF8_STRING,
            X509_LOCALITY_NAME_OID, sizeof(X509_LOCALITY_NAME_OID),
            name->localityName, name->localityNameLen, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Valid Organization Name attribute?
      if(name->organizationName != NULL && name->organizationNameLen > 0)
      {
         //Encode Organization Name attribute
         error = x509FormatNameAttribute(ASN1_TYPE_UTF8_STRING,
            X509_ORGANIZATION_NAME_OID, sizeof(X509_ORGANIZATION_NAME_OID),
            name->organizationName, name->organizationNameLen, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Valid Organizational Unit Name attribute?
      if(name->organizationalUnitName != NULL && name->organizationalUnitNameLen > 0)
      {
         //Encode Organizational Unit Name attribute
         error = x509FormatNameAttribute(ASN1_TYPE_UTF8_STRING,
            X509_ORGANIZATIONAL_UNIT_NAME_OID, sizeof(X509_ORGANIZATIONAL_UNIT_NAME_OID),
            name->organizationalUnitName, name->organizationalUnitNameLen, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Valid Common Name attribute?
      if(name->commonName != NULL && name->commonNameLen > 0)
      {
         //Encode Common Name attribute
         error = x509FormatNameAttribute(ASN1_TYPE_UTF8_STRING,
            X509_COMMON_NAME_OID, sizeof(X509_COMMON_NAME_OID),
            name->commonName, name->commonNameLen, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //The Name structure is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &n);
      //Any error to report?
      if(error)
         return error;

      //Total number of bytes that have been written
      *written = n;
   }

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format Name attribute
 * @param[in] type ASN.1 string type
 * @param[in] oid Attribute OID
 * @param[in] oidLen Length of the attribute OID, in bytes
 * @param[in] value Attribute value
 * @param[in] valueLen Length of the attribute value, in bytes
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatNameAttribute(uint_t type, const uint8_t *oid, size_t oidLen,
   const char_t *value, size_t valueLen, uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //Format AttributeType field
   tag.constructed = FALSE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
   tag.length = oidLen;
   tag.value = oid;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format AttributeValue field
   tag.constructed = FALSE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = type;
   tag.length = valueLen;
   tag.value = (uint8_t *) value;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The attribute type and value are encapsulated within a sequence
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //The sequence is encapsulated within a set
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_SET;
   tag.length = n;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format Validity structure
 * @param[in] validity Validity period
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatValidity(const X509Validity *validity, uint8_t *output,
   size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The NotBefore field may be encoded as UTCTime or GeneralizedTime
   error = x509FormatTime(&validity->notBefore, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The NotAfter field may be encoded as UTCTime or GeneralizedTime
   error = x509FormatTime(&validity->notAfter, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The Validity structure is encapsulated within a sequence
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format UTCTime or GeneralizedTime field
 * @param[in] dateTime Date to be encoded
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatTime(const DateTime *dateTime, uint8_t *output,
   size_t *written)
{
   error_t error;
   uint_t type;
   size_t n;
   Asn1Tag tag;
   char_t buffer[16];

   //UTCTime is limited to the period from 1950 to 2049
   if(dateTime->year >= 1950 && dateTime->year <= 2049)
   {
      //Use UTCTime format
      type = ASN1_TYPE_UTC_TIME;

      //The UTCTime uses a 2-digit representation of the year. If YY is greater
      //than or equal to 50, the year shall be interpreted as 19YY. If YY is
      //less than 50, the year shall be interpreted as 20YY
      sprintf(buffer, "%02" PRIu16 "%02" PRIu8 "%02" PRIu8
         "%02" PRIu8 "%02" PRIu8 "%02" PRIu8 "Z",
         dateTime->year % 100, dateTime->month, dateTime->day,
         dateTime->hours, dateTime->minutes, dateTime->seconds);
   }
   else
   {
      //Use GeneralizedTime format
      type = ASN1_TYPE_GENERALIZED_TIME;

      //The GeneralizedTime uses a 4-digit representation of the year
      sprintf(buffer, "%04" PRIu16 "%02" PRIu8 "%02" PRIu8
         "%02" PRIu8 "%02" PRIu8 "%02" PRIu8 "Z",
         dateTime->year, dateTime->month, dateTime->day,
         dateTime->hours, dateTime->minutes, dateTime->seconds);
   }

   //The date may be encoded as UTCTime or GeneralizedTime
   tag.constructed = FALSE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = type;
   tag.length = cryptoStrlen(buffer);
   tag.value = (uint8_t *) buffer;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format Extensions structure
 * @param[in] extensions Pointer to the X.509 extensions
 * @param[in] subjectKeyId SubjectKeyIdentifier extension
 * @param[in] authKeyId AuthorityKeyIdentifier extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatExtensions(const X509Extensions *extensions,
   const X509SubjectKeyId *subjectKeyId, const X509AuthorityKeyId *authKeyId,
   uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //Format NetscapeCertType extension
   error = x509FormatNsCertType(&extensions->nsCertType, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format BasicConstraints extension
   error = x509FormatBasicConstraints(&extensions->basicConstraints, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format KeyUsage extension
   error = x509FormatKeyUsage(&extensions->keyUsage, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format x509ParseSubjectKeyId extension
   error = x509FormatSubjectKeyId(subjectKeyId, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format AuthorityKeyId extension
   error = x509FormatAuthorityKeyId(authKeyId, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Format SubjectAltName extension
   error = x509FormatSubjectAltName(&extensions->subjectAltName, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //Any extensions written?
   if(length > 0)
   {
      //The extensions are encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &n);
      //Any error to report?
      if(error)
         return error;

      //Explicit tagging shall be used to encode the Extensions structure
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_CONTEXT_SPECIFIC;
      tag.objType = 3;
      tag.length = n;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format BasicConstraints extension
 * @param[in] basicConstraints Value of the extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatBasicConstraints(const X509BasicConstraints *basicConstraints,
   uint8_t *output, size_t *written)
{
   error_t error;
   uint32_t value;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;
   uint8_t buffer[3];

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The basic constraints extension identifies whether the subject of the
   //certificate is a CA and the maximum depth of valid certification paths
   //that include this certificate
   if(basicConstraints->cA || basicConstraints->critical)
   {
      //Format the extension identifier
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
      tag.length = sizeof(X509_BASIC_CONSTRAINTS_OID);
      tag.value = X509_BASIC_CONSTRAINTS_OID;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Advance data pointer
      p += n;
      length += n;

      //An extension includes the critical flag, with a default value of FALSE
      if(basicConstraints->critical)
      {
         //Mark the extension as critical
         buffer[0] = 0xFF;

         //Format the critical field
         tag.constructed = FALSE;
         tag.objClass = ASN1_CLASS_UNIVERSAL;
         tag.objType = ASN1_TYPE_BOOLEAN;
         tag.length = 1;
         tag.value = buffer;

         //Write the corresponding ASN.1 tag
         error = asn1WriteTag(&tag, FALSE, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Total number of bytes that have been written
      *written = length;

      //Length of the extension value
      length = 0;

      //Check whether the cA boolean is set
      if(basicConstraints->cA)
      {
         //The cA boolean indicates whether the certified public key may be used
         //to verify certificate signatures
         buffer[0] = 0xFF;

         //Format the cA field
         tag.constructed = FALSE;
         tag.objClass = ASN1_CLASS_UNIVERSAL;
         tag.objType = ASN1_TYPE_BOOLEAN;
         tag.length = 1;
         tag.value = buffer;

         //Write the corresponding ASN.1 tag
         error = asn1WriteTag(&tag, FALSE, p, &length);
         //Any error to report?
         if(error)
            return error;

         //Where pathLenConstraint does not appear, no limit is imposed
         if(basicConstraints->pathLenConstraint >= 0)
         {
            //The pathLenConstraint field gives the maximum number of non-self-issued
            //intermediate certificates that may follow this certificate in a valid
            //certification path
            value = basicConstraints->pathLenConstraint;

            //Encode pathLenConstraint value
            error = asn1WriteInt32(value, FALSE, p + length, &n);

            //Update the length of the extension value
            length += n;
         }
      }

      //The BasicConstraints extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The extension value is encapsulated in an octet string
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output + *written, &n);
      //Any error to report?
      if(error)
         return error;

      //Adjust the length of the extension
      *written += n;

      //The extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = *written;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format KeyUsage extension
 * @param[in] keyUsage Value of the extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatKeyUsage(const X509KeyUsage *keyUsage, uint8_t *output,
   size_t *written)
{
   error_t error;
   uint_t k;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;
   uint8_t buffer[3];

   //Initialize status code
   error = NO_ERROR;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The key usage extension defines the purpose of the key contained in the
   //certificate
   if(keyUsage->bitmap != 0 || keyUsage->critical)
   {
      //Format the extension identifier
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
      tag.length = sizeof(X509_KEY_USAGE_OID);
      tag.value = X509_KEY_USAGE_OID;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Advance data pointer
      p += n;
      length += n;

      //An extension includes the critical flag, with a default value of FALSE
      if(keyUsage->critical)
      {
         //Mark the extension as critical
         buffer[0] = 0xFF;

         //Format the critical field
         tag.constructed = FALSE;
         tag.objClass = ASN1_CLASS_UNIVERSAL;
         tag.objType = ASN1_TYPE_BOOLEAN;
         tag.length = 1;
         tag.value = buffer;

         //Write the corresponding ASN.1 tag
         error = asn1WriteTag(&tag, FALSE, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Calculate the length, in bits, of the KeyUsage value
      for(k = 16; k > 0; k--)
      {
         if(keyUsage->bitmap & (1 << (k - 1)))
            break;
      }

      //Total number of bytes needed to encode the KeyUsage value
      n = 0;

      //Encode bit string value
      if(k <= 8)
      {
         buffer[n++] = 8 - k;
         buffer[n++] = reverseInt8(keyUsage->bitmap & 0xFF);
      }
      else
      {
         buffer[n++] = 16 - k;
         buffer[n++] = reverseInt8(keyUsage->bitmap & 0xFF);
         buffer[n++] = reverseInt8((keyUsage->bitmap >> 8) & 0xFF);
      }

      //Format the bit string using ASN.1
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_BIT_STRING;
      tag.length = n;
      tag.value = buffer;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The extension value is encapsulated in an octet string
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Adjust the length of the extension
      length += n;

      //The extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format SubjectAltName extension
 * @param[in] subjectAltName Value of the extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatSubjectAltName(const X509SubjectAltName *subjectAltName,
   uint8_t *output, size_t *written)
{
   error_t error;
   uint_t i;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Initialize status code
   error = NO_ERROR;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The subject alternative name extension allows identities to be bound to the
   //subject of the certificate. These identities may be included in addition
   //to or in place of the identity in the subject field of the certificate
   if(subjectAltName->numGeneralNames > 0)
   {
      //Format the extension identifier
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
      tag.length = sizeof(X509_SUBJECT_ALT_NAME_OID);
      tag.value = X509_SUBJECT_ALT_NAME_OID;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Advance data pointer
      p += n;
      //Total number of bytes that have been written
      *written = n;

      //Loop through subject alternative names
      for(i = 0; i < subjectAltName->numGeneralNames; i++)
      {
         //Format the current name
         tag.constructed = FALSE;
         tag.objClass = ASN1_CLASS_CONTEXT_SPECIFIC;
         tag.objType = subjectAltName->generalNames[i].type;
         tag.length = subjectAltName->generalNames[i].length;
         tag.value = (uint8_t *) subjectAltName->generalNames[i].value;

         //Write the corresponding ASN.1 tag
         error = asn1WriteTag(&tag, FALSE, p, &n);
         //Any error to report?
         if(error)
            return error;

         //Advance data pointer
         p += n;
         length += n;
      }

      //Point to the first object
      p = output + *written;

      //The names are encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The extension value is encapsulated in an octet string
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Adjust the length of the extension
      *written += n;

      //The extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = *written;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format SubjectKeyIdentifier extension
 * @param[in] subjectKeyId Value of the extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatSubjectKeyId(const X509SubjectKeyId *subjectKeyId,
   uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Initialize status code
   error = NO_ERROR;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The subject key identifier extension provides a means of identifying
   //certificates that contain a particular public key
   if(subjectKeyId->value != NULL && subjectKeyId->length > 0)
   {
      //Format the extension identifier
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
      tag.length = sizeof(X509_SUBJECT_KEY_ID_OID);
      tag.value = X509_SUBJECT_KEY_ID_OID;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Advance data pointer
      p += n;
      length += n;

      //Format the KeyIdentifier field
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = subjectKeyId->length;
      tag.value = subjectKeyId->value;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The extension value is encapsulated in an octet string
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Adjust the length of the extension
      length += n;

      //The extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format AuthorityKeyIdentifier extension
 * @param[in] authKeyId Value of the extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatAuthorityKeyId(const X509AuthorityKeyId *authKeyId,
   uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;

   //Initialize status code
   error = NO_ERROR;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The authority key identifier extension provides a means of identifying the
   //public key corresponding to the private key used to sign a certificate
   if(authKeyId->keyId != NULL && authKeyId->keyIdLen > 0)
   {
      //Format the extension identifier
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
      tag.length = sizeof(X509_AUTHORITY_KEY_ID_OID);
      tag.value = X509_AUTHORITY_KEY_ID_OID;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Advance data pointer
      p += n;
      length += n;

      //Explicit tagging shall be used to encode the keyIdentifier field
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_CONTEXT_SPECIFIC;
      tag.objType = 0;
      tag.length = authKeyId->keyIdLen;
      tag.value = authKeyId->keyId;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The KeyIdentifier field is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The extension value is encapsulated in an octet string
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Adjust the length of the extension
      length += n;

      //The extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format NetscapeCertType extension
 * @param[in] nsCertType Value of the extension
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatNsCertType(const X509NsCertType *nsCertType,
   uint8_t *output, size_t *written)
{
   error_t error;
   uint_t k;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;
   uint8_t buffer[2];

   //Initialize status code
   error = NO_ERROR;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //The NetscapeCertType extension limit the use of a certificate
   if(nsCertType->bitmap != 0)
   {
      //Format the extension identifier
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
      tag.length = sizeof(X509_NS_CERT_TYPE_OID);
      tag.value = X509_NS_CERT_TYPE_OID;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Advance data pointer
      p += n;
      length += n;

      //Calculate the length, in bits, of the NetscapeCertType value
      for(k = 8; k > 0; k--)
      {
         if(nsCertType->bitmap & (1 << (k - 1)))
            break;
      }

      //Encode bit string value
      buffer[0] = 8 - k;
      buffer[1] = reverseInt8(nsCertType->bitmap);

      //Format the bit string using ASN.1
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_BIT_STRING;
      tag.length = sizeof(buffer);
      tag.value = buffer;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //The extension value is encapsulated in an octet string
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_OCTET_STRING;
      tag.length = n;
      tag.value = p;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
      //Any error to report?
      if(error)
         return error;

      //Adjust the length of the extension
      length += n;

      //The extension is encapsulated within a sequence
      tag.constructed = TRUE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_SEQUENCE;
      tag.length = length;
      tag.value = output;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, output, &length);
      //Any error to report?
      if(error)
         return error;
   }

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format SignatureAlgorithm structure
 * @param[in] signatureAlgo Pointer to the SignatureAlgorithm structure
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatSignatureAlgo(const X509SignatureAlgoId *signatureAlgo,
   uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   size_t length;
   uint8_t *p;
   Asn1Tag tag;
   X509SignatureAlgo signAlgo;
   const HashAlgo *hashAlgo;

   //Point to the buffer where to write the ASN.1 structure
   p = output;
   //Length of the ASN.1 structure
   length = 0;

   //Retrieve the signature algorithm that will be used to sign the certificate
   error = x509GetSignHashAlgo(signatureAlgo, &signAlgo, &hashAlgo);
   //Unsupported signature algorithm?
   if(error)
      return error;

   //The Algorithm field contains the OID for the algorithm used by the CA
   //to sign the certificate
   tag.constructed = FALSE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_OBJECT_IDENTIFIER;
   tag.length = signatureAlgo->oidLen;
   tag.value = signatureAlgo->oid;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, p, &n);
   //Any error to report?
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

#if (X509_RSA_SUPPORT == ENABLED && RSA_SUPPORT == ENABLED)
   //RSA signature algorithm?
   if(signAlgo == X509_SIGN_ALGO_RSA)
   {
      //For RSA signature algorithm, the parameters component of that type
      //shall be the ASN.1 type NULL (refer to RFC 3279, section 2.2.1)
      tag.constructed = FALSE;
      tag.objClass = ASN1_CLASS_UNIVERSAL;
      tag.objType = ASN1_TYPE_NULL;
      tag.length = 0;
      tag.value = NULL;

      //Write the corresponding ASN.1 tag
      error = asn1WriteTag(&tag, FALSE, p, &n);
   }
   else
#endif
#if (X509_RSA_PSS_SUPPORT == ENABLED && RSA_SUPPORT == ENABLED)
   //RSA-PSS signature algorithm?
   if(signAlgo == X509_SIGN_ALGO_RSA_PSS)
   {
      //The parameters must be present when used in the algorithm identifier
      //associated with a signature value (refer to RFC 4055, section 3.1)
      error = x509FormatRsaPssParameters(&signatureAlgo->rsaPssParams, p, &n);
   }
   else
#endif
#if (X509_DSA_SUPPORT == ENABLED && DSA_SUPPORT == ENABLED)
   //DSA signature algorithm?
   if(signAlgo == X509_SIGN_ALGO_DSA)
   {
      //For DSA signature algorithm, the encoding shall omit the parameters
      //field (refer to RFC 3279, section 2.2.2)
      n = 0;
   }
   else
#endif
#if (X509_ECDSA_SUPPORT == ENABLED && ECDSA_SUPPORT == ENABLED)
   //ECDSA signature algorithm?
   if(signAlgo == X509_SIGN_ALGO_ECDSA)
   {
      //For ECDSA signature algorithm, the encoding must omit the parameters
      //field (refer to RFC 3279, section 2.2.3)
      n = 0;
   }
   else
#endif
#if (X509_ED25519_SUPPORT == ENABLED && ED25519_SUPPORT == ENABLED)
   //Ed25519 signature algorithm?
   if(signAlgo == X509_SIGN_ALGO_ED25519)
   {
      //The parameters must be absent (refer to RFC 8410, section 6)
      n = 0;
   }
   else
#endif
#if (X509_ED448_SUPPORT == ENABLED && ED448_SUPPORT == ENABLED)
   //Ed448 signature algorithm?
   if(signAlgo == X509_SIGN_ALGO_ED448)
   {
      //The parameters must be absent (refer to RFC 8410, section 6)
      n = 0;
   }
   else
#endif
   //Invalid signature algorithm?
   {
      //Report an error
      error = ERROR_UNSUPPORTED_SIGNATURE_ALGO;
   }

   //Check status code
   if(error)
      return error;

   //Advance data pointer
   p += n;
   length += n;

   //The Algorithm and Parameters fields are encapsulated within a sequence
   tag.constructed = TRUE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_SEQUENCE;
   tag.length = length;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &length);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = length;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Format SignatureValue field
 * @param[in] prngAlgo PRNG algorithm
 * @param[in] prngContext Pointer to the PRNG context
 * @param[in] tbsCert Pointer to the TBSCertificate to be signed
 * @param[in] tbsCertLen Length of the TBSCertificate, in bytes
 * @param[in] signatureAlgoId Signature algorithm identifier
 * @param[in] publicKeyInfo Signer's public key information
 * @param[in] privateKey Signer's private key
 * @param[out] output Buffer where to format the ASN.1 structure
 * @param[out] written Length of the resulting ASN.1 structure
 * @return Error code
 **/

error_t x509FormatSignatureValue(const PrngAlgo *prngAlgo, void *prngContext,
   const uint8_t *tbsCert, size_t tbsCertLen, const X509SignatureAlgoId *signatureAlgoId,
   const X509SubjectPublicKeyInfo *publicKeyInfo, const void *privateKey,
   uint8_t *output, size_t *written)
{
   error_t error;
   size_t n;
   Asn1Tag tag;

   //The bit string shall contain an initial octet which encodes the number
   //of unused bits in the final subsequent octet
   output[0] = 0;

   //The ASN.1 DER-encoded tbsCertificate is used as the input to the signature
   //function
   error = x509GenerateSignature(prngAlgo, prngContext, tbsCert, tbsCertLen,
      signatureAlgoId, publicKeyInfo, privateKey, output + 1, &n);
   //Any error to report?
   if(error)
      return error;

   //The signature is encapsulated within a bit string
   tag.constructed = FALSE;
   tag.objClass = ASN1_CLASS_UNIVERSAL;
   tag.objType = ASN1_TYPE_BIT_STRING;
   tag.length = n + 1;
   tag.value = output;

   //Write the corresponding ASN.1 tag
   error = asn1WriteTag(&tag, FALSE, output, &n);
   //Any error to report?
   if(error)
      return error;

   //Total number of bytes that have been written
   *written = n;

   //Successful processing
   return NO_ERROR;
}


/**
 * @brief Certificate signature generation
 * @param[in] prngAlgo PRNG algorithm
 * @param[in] prngContext Pointer to the PRNG context
 * @param[in] tbsCert Pointer to the TBSCertificate to be signed
 * @param[in] tbsCertLen Length of the TBSCertificate, in bytes
 * @param[in] signatureAlgoId Signature algorithm identifier
 * @param[in] publicKeyInfo Signer's public key information
 * @param[in] privateKey Signer's private key
 * @param[out] output Resulting signature
 * @param[out] written Length of the resulting signature
 * @return Error code
 **/

error_t x509GenerateSignature(const PrngAlgo *prngAlgo, void *prngContext,
   const uint8_t *tbsCert, size_t tbsCertLen, const X509SignatureAlgoId *signatureAlgoId,
   const X509SubjectPublicKeyInfo *publicKeyInfo, const void *privateKey,
   uint8_t *output, size_t *written)
{
   error_t error;
   X509SignatureAlgo signAlgo;
   const HashAlgo *hashAlgo;
   uint8_t digest[X509_MAX_HASH_DIGEST_SIZE];

   //Retrieve the signature algorithm that will be used to sign the certificate
   error = x509GetSignHashAlgo(signatureAlgoId, &signAlgo, &hashAlgo);
   //Unsupported signature algorithm?
   if(error)
      return error;

   //Ed25519 and Ed448 are used in PureEdDSA mode, without pre-hashing
   if(hashAlgo != NULL)
   {
      //Digest the TBSCertificate structure using the specified hash algorithm
      error = hashAlgo->compute(tbsCert, tbsCertLen, digest);
      //Any error to report?
      if(error)
         return error;

#if (X509_RSA_SUPPORT == ENABLED && RSA_SUPPORT == ENABLED)
      //RSA signature algorithm?
      if(signAlgo == X509_SIGN_ALGO_RSA)
      {
         //Generate RSA signature
         error = rsassaPkcs1v15Sign(privateKey, hashAlgo, digest, output,
            written);
      }
      else
#endif
#if (X509_RSA_PSS_SUPPORT == ENABLED && RSA_SUPPORT == ENABLED)
      //RSA-PSS signature algorithm?
      if(signAlgo == X509_SIGN_ALGO_RSA_PSS)
      {
         //Generate RSA-PSS signature
         error = rsassaPssSign(prngAlgo, prngContext, privateKey, hashAlgo,
            signatureAlgoId->rsaPssParams.saltLen, digest, output, written);
      }
      else
#endif
#if (X509_DSA_SUPPORT == ENABLED && DSA_SUPPORT == ENABLED)
      //DSA signature algorithm?
      if(signAlgo == X509_SIGN_ALGO_DSA)
      {
         DsaSignature signature;

         //Initialize DSA signature
         dsaInitSignature(&signature);

         //Generate DSA signature
         error = dsaGenerateSignature(prngAlgo, prngContext, privateKey,
            digest, hashAlgo->digestSize, &signature);

         //Check status code
         if(!error)
         {
            //Encode DSA signature using ASN.1
            error = dsaWriteSignature(&signature, output, written);
         }

         //Release previously allocated resources
         dsaFreeSignature(&signature);
      }
      else
#endif
#if (X509_ECDSA_SUPPORT == ENABLED && ECDSA_SUPPORT == ENABLED)
      //ECDSA signature algorithm?
      if(signAlgo == X509_SIGN_ALGO_ECDSA)
      {
         const EcCurveInfo *curveInfo;
         EcDomainParameters params;
         EcdsaSignature signature;

         //Initialize EC domain parameters
         ecInitDomainParameters(&params);
         //Initialize ECDSA signature
         ecdsaInitSignature(&signature);

         //Retrieve EC domain parameters
         curveInfo = x509GetCurveInfo(publicKeyInfo->ecParams.namedCurve,
            publicKeyInfo->ecParams.namedCurveLen);

         //Make sure the specified elliptic curve is supported
         if(curveInfo != NULL)
         {
            //Load EC domain parameters
            error = ecLoadDomainParameters(&params, curveInfo);
         }
         else
         {
            //Invalid EC domain parameters
            error = ERROR_BAD_CERTIFICATE;
         }

         //Check status code
         if(!error)
         {
            //Generate ECDSA signature
            error = ecdsaGenerateSignature(prngAlgo, prngContext, &params,
               privateKey, digest, hashAlgo->digestSize, &signature);
         }

         //Check status code
         if(!error)
         {
            //Encode ECDSA signature using ASN.1
            error = ecdsaWriteSignature(&signature, output, written);
         }

         //Release previously allocated resources
         ecFreeDomainParameters(&params);
         ecdsaFreeSignature(&signature);
      }
      else
#endif
      //Invalid signature algorithm?
      {
         //Report an error
         error = ERROR_UNSUPPORTED_SIGNATURE_ALGO;
      }
   }
   else
   {
#if (X509_ED25519_SUPPORT == ENABLED && ED25519_SUPPORT == ENABLED)
      //Ed25519 signature algorithm?
      if(signAlgo == X509_SIGN_ALGO_ED25519)
      {
         const EddsaPrivateKey *eddsaPrivateKey;

         //Point to the EdDSA private key
         eddsaPrivateKey = (const EddsaPrivateKey *) privateKey;

         //Check the length of the EdDSA private key
         if(mpiGetByteLength(&eddsaPrivateKey->d) == ED25519_PRIVATE_KEY_LEN)
         {
            uint8_t d[ED25519_PRIVATE_KEY_LEN];

            //Retrieve private key
            error = mpiExport(&eddsaPrivateKey->d, d, ED25519_PRIVATE_KEY_LEN,
               MPI_FORMAT_LITTLE_ENDIAN);

            //Check status code
            if(!error)
            {
               //Generate Ed25519 signature (PureEdDSA mode)
               error = ed25519GenerateSignature(d, NULL, tbsCert, tbsCertLen,
                  NULL, 0, 0, output);
            }

            //Length of the resulting EdDSA signature
            *written = ED25519_SIGNATURE_LEN;
         }
         else
         {
            //The length of the EdDSA private key is not valid
            error = ERROR_INVALID_KEY;
         }
      }
      else
#endif
#if (X509_ED448_SUPPORT == ENABLED && ED448_SUPPORT == ENABLED)
      //Ed448 signature algorithm?
      if(signAlgo == X509_SIGN_ALGO_ED448)
      {
         const EddsaPrivateKey *eddsaPrivateKey;

         //Point to the EdDSA private key
         eddsaPrivateKey = (const EddsaPrivateKey *) privateKey;

         //Check the length of the EdDSA private key
         if(mpiGetByteLength(&eddsaPrivateKey->d) == ED448_PRIVATE_KEY_LEN)
         {
            uint8_t d[ED448_PRIVATE_KEY_LEN];

            //Retrieve private key
            error = mpiExport(&eddsaPrivateKey->d, d, ED448_PRIVATE_KEY_LEN,
               MPI_FORMAT_LITTLE_ENDIAN);

            //Check status code
            if(!error)
            {
               //Generate Ed448 signature (PureEdDSA mode)
               error = ed448GenerateSignature(d, NULL, tbsCert, tbsCertLen,
                  NULL, 0, 0, output);
            }

            //Length of the resulting EdDSA signature
            *written = ED448_SIGNATURE_LEN;
         }
         else
         {
            //The length of the EdDSA private key is not valid
            error = ERROR_INVALID_KEY;
         }
      }
      else
#endif
      //Invalid signature algorithm?
      {
         //Report an error
         error = ERROR_UNSUPPORTED_SIGNATURE_ALGO;
      }
   }

   //Return status code
   return error;
}

#endif
