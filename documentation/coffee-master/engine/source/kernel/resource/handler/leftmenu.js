function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6316\" class=\"headerLeftMenuInActive\"><a id=\"aID6316\" href=\"#\" OnMouseOver=\"link('_dir','handler0',this)\" class=\"leftMenuLinkHeadInActive\">handler</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID799\" class=\"leftMenuInActive\"><a id=\"aID799\" href=\"#\" OnMouseOver=\"link('_class','Handler24673',this)\" class=\"leftMenuLinkInActive\">Handler<></a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Attributes</div>\n");
document.write("<div id=\"divID1275\" class=\"leftMenuInActive\"><a id=\"aID1275\" href=\"#\" OnMouseOver=\"link('_member','Handler812731585',this)\" class=\"leftMenuLinkInActive\">Handler</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6218\" class=\"leftMenuInActive\"><a id=\"aID6218\" href=\"#\" OnMouseOver=\"link('_member','HANDLER_STATE812731585',this)\" class=\"leftMenuLinkInActive\">HANDLER_STATE</a></div>\n");
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
