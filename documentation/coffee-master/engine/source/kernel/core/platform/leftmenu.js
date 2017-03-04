function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6299\" class=\"headerLeftMenuInActive\"><a id=\"aID6299\" href=\"#\" OnMouseOver=\"link('_dir','platform0',this)\" class=\"leftMenuLinkHeadInActive\">platform</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID766\" class=\"leftMenuInActive\"><a id=\"aID766\" href=\"#\" OnMouseOver=\"link('_class','Platform58373',this)\" class=\"leftMenuLinkInActive\">Platform</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Macros</div>\n");
document.write("<div id=\"divID602\" class=\"leftMenuInActive\"><a id=\"aID602\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_EnableFlag4103909381',this)\" class=\"leftMenuLinkInActive\">COFFEE_EnableFlag</a></div>\n");
document.write("<div id=\"divID601\" class=\"leftMenuInActive\"><a id=\"aID601\" href=\"#\" OnMouseOver=\"link('_member','COFFEE_IsFlagEnabled2710252842',this)\" class=\"leftMenuLinkInActive\">COFFEE_IsFlagEnabled</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Defines</div>\n");
document.write("<div id=\"divID594\" class=\"leftMenuInActive\"><a id=\"aID594\" href=\"#\" OnMouseOver=\"link('_member','int162712012532',this)\" class=\"leftMenuLinkInActive\">int16</a></div>\n");
document.write("<div id=\"divID595\" class=\"leftMenuInActive\"><a id=\"aID595\" href=\"#\" OnMouseOver=\"link('_member','int322712012532',this)\" class=\"leftMenuLinkInActive\">int32</a></div>\n");
document.write("<div id=\"divID593\" class=\"leftMenuInActive\"><a id=\"aID593\" href=\"#\" OnMouseOver=\"link('_member','int82712012532',this)\" class=\"leftMenuLinkInActive\">int8</a></div>\n");
document.write("<div id=\"divID600\" class=\"leftMenuInActive\"><a id=\"aID600\" href=\"#\" OnMouseOver=\"link('_member','NONE2712012532',this)\" class=\"leftMenuLinkInActive\">NONE</a></div>\n");
document.write("<div id=\"divID598\" class=\"leftMenuInActive\"><a id=\"aID598\" href=\"#\" OnMouseOver=\"link('_member','NULL2712012532',this)\" class=\"leftMenuLinkInActive\">NULL</a></div>\n");
document.write("<div id=\"divID599\" class=\"leftMenuInActive\"><a id=\"aID599\" href=\"#\" OnMouseOver=\"link('_member','NULL_CHAR2712012532',this)\" class=\"leftMenuLinkInActive\">NULL_CHAR</a></div>\n");
document.write("<div id=\"divID586\" class=\"leftMenuInActive\"><a id=\"aID586\" href=\"#\" OnMouseOver=\"link('_member','real2712012532',this)\" class=\"leftMenuLinkInActive\">real</a></div>\n");
document.write("<div id=\"divID589\" class=\"leftMenuInActive\"><a id=\"aID589\" href=\"#\" OnMouseOver=\"link('_member','real642712012532',this)\" class=\"leftMenuLinkInActive\">real64</a></div>\n");
document.write("<div id=\"divID591\" class=\"leftMenuInActive\"><a id=\"aID591\" href=\"#\" OnMouseOver=\"link('_member','uint162712012532',this)\" class=\"leftMenuLinkInActive\">uint16</a></div>\n");
document.write("<div id=\"divID592\" class=\"leftMenuInActive\"><a id=\"aID592\" href=\"#\" OnMouseOver=\"link('_member','uint322712012532',this)\" class=\"leftMenuLinkInActive\">uint32</a></div>\n");
document.write("<div id=\"divID590\" class=\"leftMenuInActive\"><a id=\"aID590\" href=\"#\" OnMouseOver=\"link('_member','uint82712012532',this)\" class=\"leftMenuLinkInActive\">uint8</a></div>\n");
document.write("<div id=\"divID596\" class=\"leftMenuInActive\"><a id=\"aID596\" href=\"#\" OnMouseOver=\"link('_member','ulong2712012532',this)\" class=\"leftMenuLinkInActive\">ulong</a></div>\n");
document.write("<div id=\"divID597\" class=\"leftMenuInActive\"><a id=\"aID597\" href=\"#\" OnMouseOver=\"link('_member','ulong_ptr2712012532',this)\" class=\"leftMenuLinkInActive\">ulong_ptr</a></div>\n");
if(divID != "" && aID != "")
{
  var elemDiv = document.getElementById(divID);
  var elemA = document.getElementById(aID);
  if (elemDiv != undefined && elemA != undefined ) { // this is needed to abvoid crashing js on some memberpages 
    elemDiv.className = divClassName;
    elemA.className = aClassName;
  }
}
}
