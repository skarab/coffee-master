function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6309\" class=\"headerLeftMenuInActive\"><a id=\"aID6309\" href=\"#\" OnMouseOver=\"link('_dir','serializer0',this)\" class=\"leftMenuLinkHeadInActive\">serializer</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Directories</div>\n");
document.write("<div id=\"divID6310\" class=\"leftMenuInActive\"><a id=\"aID6310\" href=\"#\" OnMouseOver=\"link('_dir','stream/stream0',this)\" class=\"leftMenuLinkInActive\">stream</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID788\" class=\"leftMenuInActive\"><a id=\"aID788\" href=\"#\" OnMouseOver=\"link('_class','Serializer53261',this)\" class=\"leftMenuLinkInActive\">Serializer</a></div>\n");
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
