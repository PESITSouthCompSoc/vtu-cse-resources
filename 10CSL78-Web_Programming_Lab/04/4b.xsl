<?xml version="1.0"?>
<!-- create new namespace instance -->
<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <!-- match all -->
    <xsl:template match="/">
        <html style="text-align: center">
            <!-- create table to display -->
            <table cellspacing="0" cellpadding="7px" style="display:inline-block; margin: 50px auto; text-align: left;">
                <tr>
                    <th style="border-bottom: 2px solid #212121;">USN</th>
                    <th style="border-bottom: 2px solid #212121;">Name</th>
                    <th style="border-bottom: 2px solid #212121;">College</th>
                    <th style="border-bottom: 2px solid #212121;">Branch</th>
                    <th style="border-bottom: 2px solid #212121;">Year</th>
                    <th style="border-bottom: 2px solid #212121;">Email-ID</th>
                </tr>
                <xsl:for-each select="student/info">
                    <tr>
                        <!-- get each value -->
                        <td><xsl:value-of select="usn" /></td>
                        <td><xsl:value-of select="name" /></td>
                        <td><xsl:value-of select="coll" /></td>
                        <td><xsl:value-of select="branch" /></td>
                        <td><xsl:value-of select="yoj" /></td>
                        <td><xsl:value-of select="email" /></td>
                    </tr>
                </xsl:for-each>
            </table>
        </html>
    </xsl:template>
</xsl:stylesheet>