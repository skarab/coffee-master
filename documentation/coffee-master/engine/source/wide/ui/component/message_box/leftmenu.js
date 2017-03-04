function WriteLeftMenu(divID, aID, divClassName, aClassName)
{
document.write("<div id=\"divID6428\" class=\"headerLeftMenuInActive\"><a id=\"aID6428\" href=\"#\" OnMouseOver=\"link('_dir','message_box0',this)\" class=\"leftMenuLinkHeadInActive\">message_box</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Classes</div>\n");
document.write("<div id=\"divID961\" class=\"leftMenuInActive\"><a id=\"aID961\" href=\"#\" OnMouseOver=\"link('_class','MessageBox49249',this)\" class=\"leftMenuLinkInActive\">MessageBox</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Functions</div>\n");
document.write("<div id=\"divID4600\" class=\"leftMenuInActive\"><a id=\"aID4600\" href=\"#\" OnMouseOver=\"link('_member','DoMessageBox3658768668',this)\" class=\"leftMenuLinkInActive\">DoMessageBox</a></div>\n");
document.write("<div class=\"paragraphLeftMenu\">Types</div>\n");
document.write("<div id=\"divID6234\" class=\"leftMenuInActive\"><a id=\"aID6234\" href=\"#\" OnMouseOver=\"link('_member','MESSAGE_BOX_FLAG121877613',this)\" class=\"leftMenuLinkInActive\">MESSAGE_BOX_FLAG</a></div>\n");
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
